#include "../include/max_heap.hpp"
#include <iostream>
void Max_Heap::heapifyUp(int index) {
    if (index == 0) return;  // Estamos na raiz
    int parentIndex = (index - 1) / 2;
    if (heap[parentIndex].distancia < heap[index].distancia) {
        std::swap(heap[parentIndex], heap[index]);
        heapifyUp(parentIndex);  // Recursivamente ajusta para cima
    }
}

void Max_Heap::heapifyDown(int index) {
    int maior = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    if (leftChild < tamanho && heap[leftChild].distancia > heap[maior].distancia) {
        maior = leftChild;
    }
    if (rightChild < tamanho && heap[rightChild].distancia > heap[maior].distancia) {
        maior = rightChild;
    }
    if (maior != index) {
        std::swap(heap[index], heap[maior]);
        heapifyDown(maior);  // Recursivamente ajusta para baixo
    }
}

Max_Heap::Max_Heap(int capacidade) : capacidade(capacidade), tamanho(0) {
    heap = new Estacao_distancia[capacidade];
}

Max_Heap::~Max_Heap() {
    delete[] heap;
}

void Max_Heap::inserir( Estacao_distancia& novoElemento) {
    if (tamanho < capacidade) {
        heap[tamanho] = novoElemento;
        heapifyUp(tamanho);
        tamanho++;
    } else if (novoElemento.distancia < heap[0].distancia) {
        heap[0] = novoElemento;
        heapifyDown(0);
    }
}

Estacao_distancia Max_Heap::getMax() const {
    return heap[0];  // O maior elemento está na raiz
}

int Max_Heap::getTamanho() const {
    return tamanho;
}

void Max_Heap::extrairMax() {
    if (tamanho == 0) return;
    heap[0] = heap[tamanho - 1];
    tamanho--;
    heapifyDown(0);
}

bool Max_Heap::estaVazio() const {
    return tamanho == 0;
}

void Max_Heap::print() {
    for (int i = 0; i < tamanho; i++) {
        std::cout << heap[i].distancia << " ";
    }
    std::cout << std::endl;
}