package com.company;

import java.util.Scanner;
import java.util.Vector;

class LinkedListNode<T>
{
    private T value;
    private LinkedListNode<T> next;

    LinkedListNode(T value)
    {
        this.value = value;
        this.next = null;
    }

    public void connectNext(LinkedListNode<T> next)
    {
        this.next = next;
    }

    public LinkedListNode<T> getNext()
    {
        return this.next;
    }

    public T getValue()
    {
        return this.value;
    }

}

class LinkedList<T>
{

    private LinkedListNode<T> Root = null;
    private int size = 0;

    public int size()
    {
        return this.size;
    }

    public void addValue(T value)
    {
        ++size;
        if (Root == null)
            Root = new LinkedListNode<>(value);
        else
        {
            LinkedListNode<T> temp = Root;
            while (temp.getNext() != null)
                temp = temp.getNext();

            temp.connectNext(new LinkedListNode<T>(value));
        }
    }

    public void print()
    {
        LinkedListNode<T> current = Root;
        while (current != null)
        {
            System.out.print(current.getValue()+" ");
            current = current.getNext();
        }
    }

    private LinkedListNode<T> getElementByIndex(int index)
    {
        if (index < 0 || index >= this.size)
            return null;

        LinkedListNode<T> current = Root;

        for (int i = 0; i < index; ++i)
            current = current.getNext();

        return current;
    }

    public T getKeyByIndex(int index)
    {
        return this.getElementByIndex(index).getValue();
    }

    public void updateElementByIndex(int index, T value)
    {
        LinkedListNode<T> new_node = new LinkedListNode<>(value);
        new_node.connectNext(this.getElementByIndex(index + 1));
        this.getElementByIndex(index - 1).connectNext(new_node);
    }

    public T pop()
    {
        if (size == 0)
            return null;

        --size;
        LinkedListNode<T> penultimate = Root;

        while (penultimate.getNext().getNext() != null)
            penultimate = penultimate.getNext();

        T returnValue = penultimate.getNext().getValue();
        penultimate.connectNext(null);
        return returnValue;
    }
}

public class Main
{
    public static void main(String[] args)
    {
        //инициализация LinkedList
        LinkedList<Integer> list = new LinkedList<>(); //Создается пустой LinkedList
        for (int i = 0; i < 10; ++i)
            list.addValue(i); //Добавление какого-либо значения в конец списка
        int sz = list.size(); //Получить размер списка
        int first = list.getKeyByIndex(0), last = list.getKeyByIndex(sz - 1); // Получить значение элемента по его индексу
        int popped = list.pop(); //Вернуть значение последнего элемента списка и удалить его
        list.print(); //Напечатать список на экран
    }
}
