#pragma once

#include <stdexcept>
#include <string>

namespace TmxMapLib
{
class NullArgumentException : public std::invalid_argument
{
public:
    NullArgumentException(const std::string& argumentName)
        : std::invalid_argument(argumentName) {
    }
};

class XmlAttributeException : public std::runtime_error
{
public:
    XmlAttributeException(const std::string& attributeName)
        : std::runtime_error(attributeName) {
    }
};

class XmlElementException : public std::runtime_error
{
public:
    XmlElementException(const std::string& elementName)
        : std::runtime_error(elementName) {
    }
};

class XmlDocumentException : public std::runtime_error
{
public:
    XmlDocumentException(const std::string& documentName)
        : std::runtime_error(documentName) {
    }
};
}
