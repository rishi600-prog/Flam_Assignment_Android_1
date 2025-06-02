#include <iostream>
#include <unordered_map>
using namespace std;

class Node 
{
public:
    int key, value;
    Node* prev;
    Node* next;

    Node(int k, int v)
    {
        key = k;
        value = v;
        prev = nullptr;
        next = nullptr;
    }
};

class LRUCache 
{
private:
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    void remove(Node* node) 
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insertToFront(Node* node) 
    {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

public:
    LRUCache(int cap) 
    {
        capacity = cap;
        head = new Node(-1, -1);  
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) 
    {
        if (cache.count(key)) 
        {
            Node* node = cache[key];
            remove(node);
            insertToFront(node);
            return node->value;
        }
        return -1;
    }

    void put(int key, int value) 
    {
        if (cache.count(key)) 
        {
            Node* node = cache[key];
            node->value = value;
            remove(node);
            insertToFront(node);
        } 
        else 
        {
            if (cache.size() == capacity) 
            {
                Node* lru = tail->prev;
                remove(lru);
                cache.erase(lru->key);
                delete lru;
            }
            Node* newNode = new Node(key, value);
            insertToFront(newNode);
            cache[key] = newNode;
        }
    }

    ~LRUCache() 
    {
        Node* curr = head;
        while (curr) 
        {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};
