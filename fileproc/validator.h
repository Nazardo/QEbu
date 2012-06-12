#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>

class Validator
{
public:
    Validator();
    enum ValidatorError {
        Unknown = 0,
        ValidatorNotFound,
        DocumentNotValid,
        DocumentValid
    };

    bool validate(const QString &file, const QString &schema);
    ValidatorError error() const;
    QString returnMessage() const;
    QString validationErrorMessage() const;
    int errorRow() const;

private:
    void parseOutput();
    ValidatorError m_error;
    QString m_stderrOutput;
    QString m_returnMessage;
    QString m_validationErrorMessage;
    int m_errorRow;
};

#endif // VALIDATOR_H
