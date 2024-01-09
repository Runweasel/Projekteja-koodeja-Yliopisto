package com.example.ratikkabot

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import kotlinx.coroutines.*
import org.jsoup.Jsoup
import java.io.IOException
import java.util.*
import java.util.concurrent.TimeUnit

class MainActivity : AppCompatActivity() {

    private lateinit var ratikkaAjatTextView: TextView
    private lateinit var valittuNappula: Button

    private val coroutineScope = CoroutineScope(Dispatchers.IO)

    private val nappulaKonfiguraatiot = listOf(
        NappulaKonfiguraatio(
            R.id.haeHallilaNappula,
            "https://reittiopas.tampere.fi/pysakit/tampere%3A0827",
            "Seuraava ratikka saapuu Hallilan pysäkille Rautatieasemaa kohti"
        ),
        NappulaKonfiguraatio(
            R.id.haeRautatieasemaNappula,
            "https://reittiopas.tampere.fi/pysakit/tampere%3A0810",
            "Seuraava ratikka saapuu Rautatieaseman pysäkille Hallilaa kohti"
        ),
        NappulaKonfiguraatio(
            R.id.haeHallila_2_Nappula,
            "https://reittiopas.tampere.fi/pysakit/tampere%3A0828",
            "Seuraava ratikka saapuu Hallilan pysäkille Hervantaa kohti"
        ),
        NappulaKonfiguraatio(
            R.id.haeHervantaNappula,
            "https://reittiopas.tampere.fi/pysakit/tampere%3A0833",
            "Seuraava ratikka saapuu Hervannan pysäkille Hallilaa kohti"
        )
    )

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        ratikkaAjatTextView = findViewById(R.id.ratikkaAjatTextView)

        for (nappulaKonfiguraatio in nappulaKonfiguraatiot) {
            val nappula = findViewById<Button>(nappulaKonfiguraatio.nappulaId)
            nappula.setOnClickListener {
                valittuNappula = nappula
                haeRatikkaAjat(nappulaKonfiguraatio.url)
            }
        }
    }

    private fun haeRatikkaAjat(url: String) {
        coroutineScope.launch {
            val seuraavatRatikkaAjat = haeRatikkaAjatVerkosta(url)
            withContext(Dispatchers.Main) {
                paivitaTextView(seuraavatRatikkaAjat)
            }
        }
    }

    private suspend fun haeRatikkaAjatVerkosta(url: String): List<String> {
        return try {
            val document = Jsoup.connect(url).get()
            val aikaSolu = document.select("td.time-cell")
            val paaSolu = document.select("td.route-headsign")
            val seuraavatRatikkaAjat = mutableListOf<String>()

            for (i in 0 until aikaSolu.size) {
                val aikaSolu = aikaSolu[i]
                val paaSolu = paaSolu[i]

                val reitinAika = aikaSolu.select("span.route-time").text()
                val paa = paaSolu.select("div.headsign").text()

                if (valittuNappula.id == R.id.haeRautatieasemaNappula && paa != "Hervanta") {
                    continue
                }

                seuraavatRatikkaAjat.add(reitinAika)
            }

            seuraavatRatikkaAjat.take(6)
        } catch (e: IOException) {
            emptyList() // Palauta tyhjä lista, jos verkkoyhteysvirhe
        }
    }

    private fun paivitaTextView(seuraavatRatikkaAjat: List<String>) {

        val valitunNappulanTeksti = nappulaKonfiguraatiot.find { it.nappulaId == valittuNappula.id }?.nappulaTeksti

        if (seuraavatRatikkaAjat.isEmpty()) {
            // Kuka siellä netissä on
            ratikkaAjatTextView.text = "En pääse nettiin!"

        } else {

            val nykyinenKalenteri = Calendar.getInstance()
            val seuraavaRatikkaKalenteri = Calendar.getInstance()
            seuraavaRatikkaKalenteri.time = nykyinenKalenteri.time

            val aikaOsat = seuraavatRatikkaAjat[0].split(":")
            val tunti = aikaOsat[0].toInt()
            val minuutti = aikaOsat[1].toInt()

            seuraavaRatikkaKalenteri.set(Calendar.HOUR_OF_DAY, tunti)
            seuraavaRatikkaKalenteri.set(Calendar.MINUTE, minuutti)

            if (seuraavaRatikkaKalenteri.before(nykyinenKalenteri)) {
                seuraavaRatikkaKalenteri.add(Calendar.DAY_OF_MONTH, 1)
            }

            val aikaErotusMillisekunteina =
                seuraavaRatikkaKalenteri.timeInMillis - nykyinenKalenteri.timeInMillis
            val minuutit = TimeUnit.MILLISECONDS.toMinutes(aikaErotusMillisekunteina)
            val tunnit = minuutit / 60
            val jaavatMinuutit = minuutit % 60

            val aikaTeksti = when {
                tunnit > 0 && jaavatMinuutit > 0 -> "$tunnit tuntia ja $jaavatMinuutit minuuttia"
                tunnit > 0 -> "$tunnit tuntia"
                jaavatMinuutit > 0 -> "$jaavatMinuutit minuuttia"
                else -> "Vähemmän kuin minuutti"
            }

            val ratikkaAjatTeksti =
                "$valitunNappulanTeksti: ${seuraavatRatikkaAjat[0]} (saapuu ${aikaTeksti}).\n" +
                        "Sitten: ${seuraavatRatikkaAjat[1]}, ${seuraavatRatikkaAjat[2]}, ${seuraavatRatikkaAjat[3]}, ${seuraavatRatikkaAjat[4]}, ${seuraavatRatikkaAjat[5]}"
            ratikkaAjatTextView.text = ratikkaAjatTeksti
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        coroutineScope.cancel()
    }

    private data class NappulaKonfiguraatio(
        val nappulaId: Int,
        val url: String,
        val nappulaTeksti: String
    )
}