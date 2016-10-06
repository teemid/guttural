#ifndef GUTTURAL_STRING_H
#define GUTTURAL_STRING_H


namespace guttural
{
    class String
    {
    public:
        String (void);
        ~String (void);
    private:
        std::unique_ptr<char> str;
        Size length;
        UInt32 hash;
    };
}

#endif
