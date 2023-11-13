#ifndef ABSTRACT_SUBJECT_IMAGE_H
#define ABSTRACT_SUBJECT_IMAGE_H

class AbstractSubjectImage
{
private:
    /* data */
public:
    virtual void display() = 0;
    AbstractSubjectImage(/* args */) {}
    ~AbstractSubjectImage() {}
};

#endif // ABSTRACT_SUBJECT_IMAGE_H