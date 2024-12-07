#pragma once

namespace mt
{
    #pragma pack(push, 1)
    struct Node
    {
        int data;
        Node* next; // указатель на след элемент
    };
    #pragma pack(pop)

    void Pushback(Node* head, int value);
    void Print(Node* head);
    void Remove(Node* head, int index);
    void Clear(Node* head);
    void Make(Node*& head); 

    bool IsPalindrome(Node* head);
    bool isPrime(int value); 
    bool hasPrime(Node* head);
}