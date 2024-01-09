#include "queue.hh"
#include <iostream>

Queue::Queue(unsigned int cycle)
    : cycle_(cycle), is_green_(false)
{}

Queue::~Queue() {
    while (first_ != nullptr) {
        Vehicle* tmp = first_;
        first_ = first_->next;
        delete tmp;
    }
}

void Queue::enqueue(string const& reg) {
    if (is_green_) {
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
    } else {
        Vehicle* new_vehicle = new Vehicle{reg, nullptr};
        if (last_ != nullptr) {
            last_->next = new_vehicle;
        } else {
            first_ = new_vehicle;
        }
        last_ = new_vehicle;
    }
}

void Queue::dequeue() {
    if (first_ != nullptr) {
        Vehicle* tmp = first_;
        cout << tmp->reg_num;
        first_ = first_->next;
        delete tmp;
        if (first_ == nullptr) {
            last_ = nullptr;
        }
    }
}

void Queue::switch_light() {
    if (is_green_) {
        is_green_ = false;
        print();
    } else {
        is_green_ = true;
        unsigned int count = 0;

        if ( cycle_ && first_ == nullptr ) {
            print();
            return;
        }
        cout << "GREEN: Vehicle(s) ";
        while (count < cycle_ && first_ != nullptr) {
            dequeue();
            if (count < cycle_ - 1 && first_ != nullptr) {
                cout << " ";
            } else {
                cout << " can go on" << endl;
            }
            count++;
        }
        is_green_ = false;
    }
}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

void Queue::print() const {
    if (is_green_) {
        cout << "GREEN: ";
    } else {
        cout << "RED: ";
    }

    if (first_ == nullptr) {
        cout << "No vehicles waiting in traffic lights" << endl;
    } else {
        cout << "Vehicle(s) ";
        Vehicle* current = first_;
        while (current != nullptr) {
            cout << current->reg_num;
            if (current->next != nullptr) {
                cout << " ";
            }
            current = current->next;
        }
        if (is_green_) {
            cout << " can go on" << endl;
        } else {
            cout << " waiting in traffic lights" << endl;
        }
    }
}
