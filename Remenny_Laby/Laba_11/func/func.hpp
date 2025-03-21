#pragma once

struct Node
{
    int data;
    Node* prev;
    Node* next; 
};


bool dif_digits_three(int n);
bool all_digits_odd(int n);
bool all_digits_even(int n);

void AddBack(Node* sent, int data);
void Print(Node* sent);
void Clear(Node* sent);
void DuplicateOdd(Node* sent);
void RemoveEven(Node* sent);
void Sort(Node* sent);