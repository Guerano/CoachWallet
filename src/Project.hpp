#pragma once

#include <QString>

/**
 * @brief The Project class represents a cryptocurrency
 */
class Project
{
public:
    Project(QString const & name, QString const & tokenName);

    auto name()      const -> QString const &;
    auto tokenName() const -> QString const &;

    auto price() const -> float;

private:
    QString const _name;
    QString const _tokenName;
};

