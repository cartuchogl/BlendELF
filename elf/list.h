
elf_list_ptr* elf_create_list_ptr()
{
	elf_list_ptr *ptr;

	ptr = (elf_list_ptr*)malloc(sizeof(elf_list_ptr));
	memset(ptr, 0x0, sizeof(elf_list_ptr));

	elf_inc_obj(ELF_LIST_PTR);

	return ptr;
}

void elf_destroy_list_ptr(elf_list_ptr *ptr)
{
	if(ptr->obj) elf_dec_ref(ptr->obj);

	free(ptr);

	elf_dec_obj(ELF_LIST_PTR);
}

void elf_destroy_list_ptrs(elf_list_ptr *ptr)
{
	if(ptr->next) elf_destroy_list_ptrs(ptr->next);

	elf_destroy_list_ptr(ptr);
}

elf_list* elf_create_list()
{
	elf_list *list;

	list = (elf_list*)malloc(sizeof(elf_list));
	memset(list, 0x0, sizeof(elf_list));
	list->obj_type = ELF_LIST;
	list->obj_destr = elf_destroy_list;

	elf_inc_obj(ELF_LIST);

	return list;
}

void elf_destroy_list(void *data)
{
	elf_list *list = (elf_list*)data;

	if(list->first) elf_destroy_list_ptrs(list->first);

	free(list);

	elf_dec_obj(ELF_LIST);
}

int elf_get_list_length(elf_list *list)
{
	return list->length;
}

void elf_insert_to_list(elf_list *list, int idx, elf_object *obj)
{
	elf_list_ptr *ptr;
	elf_list_ptr *tptr;
	int i;

	if(idx < 0 || idx > list->length) return;

	i = 0;
	ptr = list->first;

	if(!ptr)
	{
		list->first = elf_create_list_ptr();
		list->first->obj = obj;
		list->last = list->first;
		list->length = 1;
	}
	else if(idx == 0)
	{
		ptr->prev = elf_create_list_ptr();
		ptr->prev->obj = obj;
		ptr->prev->next = ptr;
		list->first = ptr->prev;
		list->length++;
	}
	else if(idx == list->length)
	{
		list->last->next = elf_create_list_ptr();
		list->last->next->obj = obj;
		list->last->next->prev = list->last;
		list->last = list->last->next;
		list->length++;
	}
	else
	{
		while(i != idx)
		{
			ptr = ptr->next;
			i++;
		}
		tptr = ptr->prev;
		tptr->next = elf_create_list_ptr();
		tptr->next->obj = obj;
		tptr->next->next = ptr;
		tptr->next->prev = tptr;
		ptr->prev = tptr->next;
		list->length++;
	}

	elf_inc_ref(obj);
}

void elf_append_to_list(elf_list *list, elf_object *obj)
{
	if(!obj) return;

	if(!list->first)
	{
		list->first = elf_create_list_ptr();
		list->first->obj = obj;
		list->last = list->first;
		list->length = 1;
	}
	else
	{
		list->last->next = elf_create_list_ptr();
		list->last->next->obj = obj;
		list->last->next->prev = list->last;
		list->last = list->last->next;
		list->length++;
	}

	elf_inc_ref(obj);
}

elf_object* elf_get_item_from_list(elf_list *list, int idx)
{
	elf_list_ptr *ptr;
	int i;

	if(idx < 0 || idx > list->length-1) return NULL;

	ptr = list->first;
	i = 0;

	while(ptr)
	{
		if(i == idx)
		{
			return ptr->obj;
		}
		ptr = ptr->next;
		i++;
	}

	return NULL;
}

unsigned char elf_remove_from_list(elf_list *list, elf_object *obj)
{
	elf_list_ptr *ptr;
	elf_list_ptr *prev_ptr;

	prev_ptr = NULL;
	ptr = list->first;

	if(list->cur && obj == list->cur->obj)
	{
		prev_ptr = list->cur->prev;
		ptr = list->cur;
		list->cur = list->cur->prev;
	}

	while(ptr)
	{
		if(ptr->obj == obj)
		{
			if(prev_ptr)
			{
				prev_ptr->next = ptr->next;
				if(ptr->next) ptr->next->prev = prev_ptr;
			}
			else
			{
				list->first = ptr->next;
				if(list->first) list->first->prev = NULL;
			}
			if(ptr == list->last) list->last = ptr->prev;
			elf_destroy_list_ptr(ptr);
			list->length--;

			return ELF_TRUE;
		}
		prev_ptr = ptr;
		ptr = ptr->next;
	}

	return ELF_FALSE;
}

elf_object* elf_begin_list(elf_list *list)
{
	list->cur = list->first;
	if(list->cur)
	{
		list->next = list->cur->next;
		return list->cur->obj;
	}
	return NULL;
}

elf_object* elf_next_in_list(elf_list *list)
{
	list->cur = list->next;
	if(list->cur)
	{
		list->next = list->cur->next;
		return list->cur->obj;
	}
	return NULL;
}

elf_object* elf_rbegin_list(elf_list *list)
{
	list->cur = list->last;
	if(list->cur)
	{
		list->next = list->cur->prev;
		return list->cur->obj;
	}
	return NULL;
}

elf_object* elf_rnext_in_list(elf_list *list)
{
	list->cur = list->next;
	if(list->cur)
	{
		list->next = list->cur->prev;
		return list->cur->obj;
	}
	return NULL;
}

void elf_set_list_cur_ptr(elf_list *list, elf_object *ptr)
{
	if(list->cur)
	{
		elf_dec_ref((elf_object*)list->cur->obj);
		list->cur->obj = ptr;
		elf_inc_ref((elf_object*)list->cur->obj);
	}
}

void elf_seek_list(elf_list *list, elf_object *ptr)
{
	elf_object *obj;

	for(obj = elf_begin_list(list); obj;
		obj = elf_next_in_list(list))
	{
		if(obj == ptr) return;
	}
}

void elf_rseek_list(elf_list *list, elf_object *ptr)
{
	elf_object *obj;

	for(obj = elf_rbegin_list(list); obj;
		obj = elf_rnext_in_list(list))
	{
		if(obj == ptr) return;
	}
}

