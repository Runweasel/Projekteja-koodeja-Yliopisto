#include "cards.hh"

Cards::Cards() : top_(nullptr) {}

Card_data* Cards::get_topmost() {
    return top_;
}

void Cards::add(int id) {
    Card_data* uusi_kortti = new Card_data{id, top_};
    top_ = uusi_kortti;
}

void Cards::print_from_top_to_bottom(std::ostream& s) {
    Card_data* nykyinen = top_;
    int sijainti = 1;
    while (nykyinen != nullptr) {
        s << sijainti << ": " << nykyinen->data << std::endl;
        nykyinen = nykyinen->next;
        ++sijainti;
    }
}

bool Cards::remove(int& id) {
    if (top_ == nullptr) {
        return false;
    }
    id = top_->data;
    Card_data* vanha_top_ = top_;
    top_ = top_->next;
    delete vanha_top_;
    return true;
}

bool Cards::bottom_to_top() {
    if (top_ == nullptr || top_->next == nullptr) {
        return false;
    }
    Card_data* nykyinen = top_;
    while (nykyinen->next->next != nullptr) {
        nykyinen = nykyinen->next;
    }
    Card_data* viimeinen_kortti = nykyinen->next;
    nykyinen->next = nullptr;
    viimeinen_kortti->next = top_;
    top_ = viimeinen_kortti;
    return true;
}

bool Cards::top_to_bottom() {
    if (top_ == nullptr || top_->next == nullptr) {
        return false;
    }
    Card_data* nykyinen = top_;
    while (nykyinen->next != nullptr) {
        nykyinen = nykyinen->next;
    }
    nykyinen->next = top_;
    top_ = top_->next;
    nykyinen->next->next = nullptr;
    return true;
}

void Cards::print_from_bottom_to_top(std::ostream& s) {
    recursive_print(top_, s);
}

int Cards::recursive_print(Card_data* top_, std::ostream& s) {
    if (top_ == nullptr) {
        return 0;
    }
    int sijainti = recursive_print(top_->next, s) + 1;
    s << sijainti << ": " << top_->data << std::endl;
    return sijainti;
}

Cards::~Cards() {
    Card_data* nykyinen = top_;
    while (nykyinen != nullptr) {
        Card_data* seuraava = nykyinen->next;
        delete nykyinen;
        nykyinen = seuraava;
    }
}
