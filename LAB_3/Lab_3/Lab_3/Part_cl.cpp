#include "Part_cl.h"

part* Parts::add(part* cur)
{
	buf = new part;// ����������� ������ �� ���������� ����������
	size++; // ���������� ���������� ���������� ����� �� ����	
	if (cur == NULL && head == NULL) // ���������� ������ �����
	{
		if (head == NULL) // ���� � ������ ��� ���������
		{
			head = buf;
			tail = buf;
		}
		else // ���� ����� �������� ������ \
			 			    ������� � ������, ��� ��� \
                ��� ��� ��� ���� ��������
		{
			buf->next = head;
			head->prev = buf;
			head = buf;
			buf->prev = NULL;
			// ���� ��������� ������� ��� �����
			if (buf->next->next == NULL) {
				tail = buf->next;
				buf->next->line = 2;
			}
		}
		// ������������ ������ ������
		buf->line = 1;
	}
	else if (cur == tail) {
		if (head->next == NULL) // ���� � ������ 1-�������
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
		// ������������ ������ ������
		buf->line = count;
	}
	else // ���������� ���� ����� ��������
	{
		if (buf->next != NULL) buf->next->prev = buf;
		buf->next = cur->next;
		cur->next = buf;
		buf->prev = cur;
		// ������������ ������ ������
		buf->line = cur->line + 1;
	}
	return buf;

}
