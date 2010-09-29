
elfProperty* elfCreateProperty(const char* name)
{
	elfProperty* property;

	property = (elfProperty*)malloc(sizeof(elfProperty));
	memset(property, 0x0, sizeof(elfProperty));
	property->objType = ELF_PROPERTY;
	property->objDestr = elfDestroyProperty;

	property->propertyType = ELF_PROPERTY_INT;

	if(property) property->name = elfCreateString(name);

	elfIncObj(ELF_PROPERTY);

	return property;
}

void elfDestroyProperty(void* data)
{
	elfProperty* property = (elfProperty*)data;

	if(property->name) elfDestroyString(property->name);
	if(property->sval) elfDestroyString(property->sval);

	free(property);

	elfDecObj(ELF_PROPERTY);
}

int elfGetPropertyType(elfProperty* property)
{
	return property->propertyType;
}

int elfGetPropertyInt(elfProperty* property)
{
	return property->ival;
}

float elfGetPropertyFloat(elfProperty* property)
{
	return property->fval;
}

const char* elfGetPropertyString(elfProperty* property)
{
	return property->sval;
}

unsigned char elfGetPropertyBool(elfProperty* property)
{
	return property->bval;
}

void elfSetPropertyInt(elfProperty* property, int ival)
{
	property->propertyType = ELF_PROPERTY_INT;
	property->ival = ival;
	property->fval = 0.0;
	if(property->sval) elfDestroyString(property->sval);
	property->sval = NULL;
	property->bval = ELF_FALSE;
}

void elfSetPropertyFloat(elfProperty* property, float fval)
{
	property->propertyType = ELF_PROPERTY_FLOAT;
	property->ival = 0;
	property->fval = fval;
	if(property->sval) elfDestroyString(property->sval);
	property->sval = NULL;
	property->bval = ELF_FALSE;
}

void elfSetPropertyString(elfProperty* property, const char* sval)
{
	property->propertyType = ELF_PROPERTY_STRING;
	property->ival = 0;
	property->fval = 0.0;
	if(property->sval) elfDestroyString(property->sval);
	property->sval = elfCreateString(sval);
	property->bval = ELF_FALSE;
}

void elfSetPropertyBool(elfProperty* property, unsigned char bval)
{
	property->propertyType = ELF_PROPERTY_BOOL;
	property->ival = 0;
	property->fval = 0.0;
	if(property->sval) elfDestroyString(property->sval);
	property->sval = NULL;
	property->bval = !bval == ELF_FALSE;
}

