#include "gut_common.h"
#include "gut_memory.h"
#include "gut_string.h"


#define CStr(tagged)   (tagged)->value.string->c_str
#define Length(tagged) (tagged)->value.string->length
#define Hash(tagged)   (tagged)->value.string->hash


internal void CopyString (GutTValue * gut_string, char * c_str, Size length)
{
    for (Size i = 0; i < length; i++)
    {
        CStr(gut_string)[i] = c_str[i];
    }
}



GutTValue * GutStringNew (char * string, Size length)
{
    GutTValue * tagged_value = Allocate(GutTValue *, sizeof(GutTValue));
    tagged_value->type = TYPE_STRING;

    String(tagged_value)     = Allocate(GutString *, sizeof(GutString));
    CStr(tagged_value)       = Allocate(char *, length);

    CopyString(tagged_value, string, length);

    Length(tagged_value)     = length;
    Hash(tagged_value)       = 0;

    return tagged_value;
}


void GutStringDelete (GutTValue * string)
{
    Free(CStr(string));
    Free(String(string));
    Free(string);
}


Size GutStringLength (GutTValue * string)
{
    return Length(string);
}


Bool32 GutStringCompare (GutTValue * s1, GutTValue * s2, Size length)
{
    if (Hash(s1) && Hash(s2)) return Hash(s1) == Hash(s2);

    for (Size i = 0; i < length; i++)
    {
        if (CStr(s1)[i] != CStr(s2)[i]) { return 0; }
    }

    return 1;
}
