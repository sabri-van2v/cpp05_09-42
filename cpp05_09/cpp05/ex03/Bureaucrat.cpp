#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(std::string name, int grade):_name(name)
{
    if (grade > 150)
        throw (Bureaucrat::GradeTooLowException());
    else if (grade < 1)
        throw (Bureaucrat::GradeTooHighException());
    else
        _grade = grade;
}

Bureaucrat::Bureaucrat():_name("unknown"), _grade(150)
{}

Bureaucrat::Bureaucrat(Bureaucrat const &b):_name(b._name)
{
    *this = b;
}

Bureaucrat::~Bureaucrat()
{}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &b)
{
    _grade = b._grade;
    return (*this);
}

std::string Bureaucrat::getName()
{
    return (_name);
}

int         Bureaucrat::getGrade() const
{
    return (_grade);
}

void        Bureaucrat::increment()
{
    if (_grade == 1)
        throw Bureaucrat::GradeTooHighException();
    _grade--;
}

void        Bureaucrat::decrement()
{
    if (_grade == 150)
        throw Bureaucrat::GradeTooLowException();
    _grade++;
}

void    Bureaucrat::signForm(Form &f)
{
    if (f.getSigned() == false)
    {
        try
        {
            f.beSigned(*this);
            std::cout << *this << " signed " << f << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << _name << " couldn't sign " << f << " because " << e.what() << std::endl;
        }
    }
}

void    Bureaucrat::executeForm(Form const &form)
{
    try
    {
        form.execute_task(*this);
        std::cout << *this << " executed " << form << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << *this << " cannot execute " << form << " because " << e.what() << std::endl;
    }
}

std::ostream    &operator<<(std::ostream &o, Bureaucrat &b)
{
    o << b.getName() << ", bureaucrat grade " << b.getGrade();
    return (o);
}