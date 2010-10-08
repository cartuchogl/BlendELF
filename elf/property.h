
ELF_API elfProperty* ELF_APIENTRY elfCreateProperty(const char* name)
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

ELF_API int ELF_APIENTRY elfGetPropertyType(elfProperty* property)
{
	return property->propertyType;
}

ELF_API int ELF_APIENTRY elfGetPropertyInt(elfProperty* property)
{
	return property->ival;
}

ELF_API float ELF_APIENTRY elfGetPropertyFloat(elfProperty* property)
{
	return property->fval;
}

ELF_API const char* ELF_APIENTRY elfGetPropertyString(elfProperty* property)
{
	return property->sval;
}

ELF_API unsigned char ELF_APIENTRY elfGetPropertyBool(elfProperty* property)
{
	return property->bval;
}

ELF_API void ELF_APIENTRY elfSetPropertyInt(elfProperty* property, int ival)
{
	property->propertyType = ELF_PROPERTY_INT;
	property->ival = ival;
	property->fval = 0.0f;
	if(property->sval) elfDestroyString(property->sval);
	property->sval = NULL;
	property->bval = ELF_FALSE;
}

ELF_API void ELF_APIENTRY elfSetPropertyFloat(elfProperty* property, float fval)
{
	property->propertyType = ELF_PROPERTY_FLOAT;
	property->ival = 0;
	property->fval = fval;
	if(property->sval) elfDestroyString(property->sval);
	property->sval = NULL;
	property->bval = ELF_FALSE;
}

ELF_API void ELF_APIENTRY elfSetPropertyString(elfProperty* property, const char* sval)
{
	property->propertyType = ELF_PROPERTY_STRING;
	property->ival = 0;
	property->fval = 0.0f;
	if(property->sval) elfDestroyString(property->sval);
	property->sval = elfCreateString(sval);
	property->bval = ELF_FALSE;
}

ELF_API void ELF_APIENTRY elfSetPropertyBool(elfProperty* property, unsigned char bval)
{
	property->propertyType = ELF_PROPERTY_BOOL;
	property->ival = 0;
	property->fval = 0.0f;
	if(property->sval) elfDestroyString(property->sval);
	property->sval = NULL;
	property->bval = !bval == ELF_FALSE;
}

