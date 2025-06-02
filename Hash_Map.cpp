#include <iostream>
#include <vector>
using namespace std;

class Node 
{
public:
    int key, value;
    Node* next;
    Node(int k, int v)
    {
        key = k;
        value = v;
        next = nullptr;
    }
};

class HashMap 
{

private:
    static const int SIZE = 10007;
    vector<Node*> buckets;         

    int hash(int key) 
    {
        return key % SIZE;
    }

public:

    HashMap() 
    {
        buckets.resize(SIZE, nullptr);
    }

    void put(int key, int value) 
    {
        int index = hash(key);
        Node* head = buckets[index];

        Node* curr = head;
        while (curr != nullptr) 
        {
            if (curr->key == key) 
            {
                curr->value = value;
                return;
            }
            curr = curr->next;
        }

        Node* newNode = new Node(key, value);
        newNode->next = head;
        buckets[index] = newNode;
    }

    int get(int key) 
    {
        int index = hash(key);
        Node* curr = buckets[index];

        while (curr != nullptr) 
        {
            if (curr->key == key)
                return curr->value;
            curr = curr->next;
        }

        return -1;
    }

    void remove(int key) 
    {
        int index = hash(key);
        Node* curr = buckets[index];
        Node* prev = nullptr;

        while (curr != nullptr) 
        {
            if (curr->key == key) 
            {
                if (prev != nullptr)
                    prev->next = curr->next;
                else
                    buckets[index] = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    HashMap() 
    {
        for (int i = 0; i < SIZE; ++i) 
        {
            Node* curr = buckets[i];
            while (curr != nullptr) 
            {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }
};
