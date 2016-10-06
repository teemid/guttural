#ifndef GUTTURAL_OBJECT_H
#define GUTTURAL_OBJECT_H


namespace guttural
{
    class Object
    {
        public:
            virtual ~Object (void);
        private:
            Object (void);

            ObjectType type;
            Object * next;
            Object * prev;
    };
}

#endif
