#include "gut_core.h"
#include "gut_lexer.h"
#include "gut_string.h"


#define StringTable(state) (state)->global_state->string_table
#define Hash(tagged) (tagged)->value.string->hash


void GutCoreInitialize (GutState * state)
{
    GutTable * string_table = StringTable(state);
    GutTValue counter = { { 0 }, TYPE_INTEGER };

    for (UInt32 i = 0; i < LAST_RESERVED; i++)
    {
        Integer(&counter) = i;

        Keyword const * keyword = &guttural_keywords[i];

        GutTValue * gut_string = GutStringNew(keyword->name, keyword->length);

        UInt32 hash = string_table->hash(gut_string);

        GutTableHashAdd(string_table, hash, gut_string, &counter);
    }
}
