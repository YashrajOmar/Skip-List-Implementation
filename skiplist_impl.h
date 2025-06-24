#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <random>
#include <cmath>

using namespace std;

template <typename T>
struct Node {
    T value;
    vector<shared_ptr<Node<T>>> forward;

    Node(T val, int level) : value(val), forward(level + 1, nullptr) {}
};

template <typename T>
struct SkipList {
    int maxLevel;
    float probability;
    int currentLevel;
    int size;
    shared_ptr<Node<T>> head;

    mt19937 rng{random_device{}()};
    uniform_real_distribution<> dist{0.0, 1.0};

    SkipList(int maxN, float prob = 0.5f)
        : maxLevel(static_cast<int>(ceil(log2(maxN)))),
          probability(prob), currentLevel(0), size(0),
          head(make_shared<Node<T>>(numeric_limits<T>::max(), maxLevel)) {}

    int randomLevel() {
        int lvl = 0;
        while (dist(rng) < probability && lvl < maxLevel)
            lvl++;
        return lvl;
    }



bool insert(T value) {
    vector<shared_ptr<Node<T>>> update(maxLevel + 1);
    auto curr = head;

    for (int i = currentLevel; i >= 0; --i) {
        while (curr->forward[i] && curr->forward[i]->value < value)
            curr = curr->forward[i];
        update[i] = curr;
    }

    curr = curr->forward[0];

    if (curr && curr->value == value)
        return false;  // already present

    int newLevel = randomLevel();
    if (newLevel > currentLevel) {
        for (int i = currentLevel + 1; i <= newLevel; ++i)
            update[i] = head;
        currentLevel = newLevel;
    }

    auto newNode = make_shared<Node<T>>(value, newLevel);
    for (int i = 0; i <= newLevel; ++i) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }

    size++;
    return true;
}

    bool search(T value) const {
        auto curr = head;
        for (int i = currentLevel; i >= 0; --i) {
            while (curr->forward[i] && curr->forward[i]->value < value)
                curr = curr->forward[i];
        }
        curr = curr->forward[0];
        return curr && curr->value == value;
    }

    bool remove(T value) {
        vector<shared_ptr<Node<T>>> update(maxLevel + 1);
        auto curr = head;
        for (int i = currentLevel; i >= 0; --i) {
            while (curr->forward[i] && curr->forward[i]->value < value)
                curr = curr->forward[i];
            update[i] = curr;
        }

        curr = curr->forward[0];
        if (!curr || curr->value != value)
            return false;

        for (int i = 0; i <= currentLevel; ++i) {
            if (update[i]->forward[i] != curr)
                break;
            update[i]->forward[i] = curr->forward[i];
        }

        while (currentLevel > 0 && !head->forward[currentLevel])
            --currentLevel;

        size--;
        return true;
    }

    void display() const {
    for (int i = maxLevel; i >= 0; --i) {
        cout << "Level " << i << ": ";
        auto node = head->forward[i];
        while (node) {
            cout << node->value << " -> ";
            node = node->forward[i];
        }
        cout << "nullptr\n";
    }
}


    int getSize() const { return size; }
};
