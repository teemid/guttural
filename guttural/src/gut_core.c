#include "gut_core.h"
#include "gut_lexer.h"
#include "gut_string.h"


#define StringTable(state) (state)->global_state->string_table
#define Hash(tagged) (tagged)->value.string->hash


void GutCoreInitialize (GutState * state)
{
    GutTable * string_table = StringTable(state);

    for (UInt32 i = 0; i < LAST_RESERVED; i++)
    {
        Keyword const * keyword = &guttural_keywords[i];

        GutTValue * gut_string = GutStringNew(keyword->name, keyword->length);

        UInt32 hash = string_table->hash(gut_string);

        GutTableAddHash(string_table, gut_string, hash, gut_string);
    }
}
