#ifndef GUTTURAL_CLASS_H
#define GUTTURAL_CLASS_H


namespace guttural
{
    class Klass
    {
    public:
        Klass (void);
        ~Klass (void);
    private:
        std::unique_ptr<char> name;
    };
}

#endif
