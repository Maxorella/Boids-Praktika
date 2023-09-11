class Creature
{
public:
    Creature();
    virtual ~Creature();
protected:
    virtual void behave()=0;
    virtual void move()=0;
    
};

