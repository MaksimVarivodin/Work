#include "Part_cl.h"

part* Parts::add(part* cur)
{
	buf = new part;// копирование строки из введенного экземпляра
	size++; // увеличение переменной количества строк на один	
	if (cur == NULL && head == NULL) // Добавление нового корня
	{
		if (head == NULL) // если в списке нет элементов
		{
			head = buf;
			tail = buf;
		}
		else // если нужно добавить первый \
			 			    элемент в список, при том \
                что там уже есть элементы
		{
			buf->next = head;
			head->prev = buf;
			head = buf;
			buf->prev = NULL;
			// если следующий элемент это хвост
			if (buf->next->next == NULL) {
				tail = buf->next;
				buf->next->line = 2;
			}
		}
		// формирование номера строки
		buf->line = 1;
	}
	else if (cur == tail) {
		if (head->next == NULL) // если в списке 1-элемент
		{
			tail = buf;
			buf->prev = head;
			head->next = buf;
		}
		else {
			buf->prev = tail;
			tail->next = buf;
			tail = buf;
		}
		// формирование номера строки
		buf->line = count;
	}
	else // Добавление узла после текущего
	{
		if (buf->next != NULL) buf->next->prev = buf;
		buf->next = cur->next;
		cur->next = buf;
		buf->prev = cur;
		// формирование номера строки
		buf->line = cur->line + 1;
	}
	return buf;

}
