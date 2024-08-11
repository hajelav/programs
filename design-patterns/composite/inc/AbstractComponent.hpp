#ifndef ABSTRACT_COMPONENT_H
#define ABSTRACT_COMPONENT_H

class AbstractComponent
{
public:
    virtual void operation() = 0;
    virtual ~AbstractComponent() = default;
};

#endif /* ABSTRACT_COMPONENT_H */