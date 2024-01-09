package com.example.lassinapp;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private LinearLayout notesLayout;
    private int noteCounter = 1;
    private ArrayList<String> notesList;
    private SharedPreferences sharedPreferences;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        notesLayout = findViewById(R.id.notes_layout);
        sharedPreferences = getPreferences(Context.MODE_PRIVATE);

        loadSavedNotes();
    }

    private void loadSavedNotes() {
        noteCounter = sharedPreferences.getInt("noteCounter", 1);
        notesList = new ArrayList<>();
        for (int i = 1; i < noteCounter; i++) {
            String note = sharedPreferences.getString(String.valueOf(i), null);
            if (note != null) {
                notesList.add(note);
                addNoteToLayout(note, i);
            }
        }
    }

    public void addNoteOnClick(View view) {
        EditText noteEditText = findViewById(R.id.note_edit_text);
        String noteText = noteEditText.getText().toString();

        if (!noteText.isEmpty()) {
            notesList.add(noteText);
            addNoteToLayout(noteText, noteCounter);
            saveNoteToSharedPreferences(noteText, noteCounter);
            noteCounter++;
            saveNoteCounterToSharedPreferences(noteCounter);
            noteEditText.setText("");
        }
    }

    @SuppressLint("SetTextI18n")
    private void addNoteToLayout(String noteText, int noteNumber) {
        TextView noteTextView = new TextView(this);
        noteTextView.setText(noteNumber + ". " + noteText);
        noteTextView.setTextSize(24);
        noteTextView.setOnClickListener(v -> {
            String noteKey = ((TextView) v).getText().toString().split("\\. ")[0];
            showDeleteConfirmationDialog(noteKey, v);
        });

        notesLayout.addView(noteTextView);
    }

    private void saveNoteToSharedPreferences(String noteText, int noteNumber) {
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putString(String.valueOf(noteNumber), noteText);
        editor.apply();
    }

    private void saveNoteCounterToSharedPreferences(int noteCounter) {
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putInt("noteCounter", noteCounter);
        editor.apply();
    }

    private void deleteNoteFromSharedPreferences(String noteKey) {
        int noteNumber = Integer.parseInt(noteKey);
        notesList.remove(noteNumber - 1);
        notesLayout.removeAllViews();
        for (int i = 0; i < notesList.size(); i++) {
            String noteText = notesList.get(i);
            addNoteToLayout(noteText, i + 1);
            saveNoteToSharedPreferences(noteText, i + 1);
        }
        noteCounter--;
        saveNoteCounterToSharedPreferences(noteCounter);
    }

    private void showDeleteConfirmationDialog(String noteKey, View noteView) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Delete Note");
        builder.setMessage("Are you sure you want to delete this note?");
        builder.setPositiveButton("Yes", (dialog, which) -> {
            notesLayout.removeView(noteView);
            deleteNoteFromSharedPreferences(noteKey);
        });
        builder.setNegativeButton("No", null);
        builder.create().show();
    }
}
