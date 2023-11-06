#ifndef ABSTRACT_COMMAND_H
#define ABSTRACT_COMMAND_H


class AbstractCommand {

    public:
        virtual void execute() = 0;
        virtual void undo() = 0;

};

#endif /* ABSTRACT_COMMAND_H */
