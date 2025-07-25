#ifndef USERL3_H
#define USERL3_H

#include <QString>
#include <QDate>
#include <QMetaEnum>

class UserL3
{
    Q_GADGET
public:
    enum Sex {
        Male,
        Female
    };
    Q_ENUM(Sex)


    enum PersonalityType {
        Extravert,
        Introvert,
        Ambivient
    };
    Q_ENUM(PersonalityType)

private:



public:
    QString name;
    QString email;
    QString description;
    QDate birth_day;
    int prefered_salary;
    Sex sex;
    PersonalityType personality_type;
    QList<QString> strengths;
    QString position;

    UserL3(){
        name = "Puppet John";
        email = "mail@mail.mmm";
        description = "Lorem ipsum";
        birth_day = QDate(2001, 9, 11);
        prefered_salary = 2137;
        sex = Sex::Male;
        personality_type = PersonalityType::Ambivient;
        strengths = QList<QString>();
        position = "abc";
    }

    UserL3(QString name, QString email, QString description, QDate bday, int prefered_salary, QString string_sex, QString string_personality, QString position)
        :name (name), email(email), description(description), birth_day(bday), prefered_salary(prefered_salary), position(position)
    {
        if(string_sex == "Male"){
            sex = Sex::Male;
        }
        else if (string_sex == "Female"){
            sex = Sex::Female;
        }
        else{
            sex = Sex::Male;
        }

        if(string_personality == "Extravert"){
            personality_type = PersonalityType::Extravert;
        }
        else if (string_personality == "Introvert"){
            personality_type = PersonalityType::Introvert;
        }
        else if (string_personality == "Ambivient"){
            personality_type = PersonalityType::Ambivient;
        }
        else{
            personality_type = PersonalityType::Ambivient;
        }
    }

    QString strengthsSum() const {
        QString oneStringStrengths;

        for(int i = 0; i < strengths.size(); i++){

            oneStringStrengths += strengths[i];

            if(i + 1 != strengths.size()){
                oneStringStrengths += ' ';
            }
        }

        return oneStringStrengths;
    }

};



#endif // USERL3_H
