#ifndef I_FIELD_HPP
#define I_FIELD_HPP

#include <string>
#include <typeinfo>

#include "Utilities.hpp"

// Supported Types: int, char, float, bool, std::string, (Compounds) Vector2D, Transform2D
class IField {
public:
    IField(std::string name = {}) 
        : name_(name) 
    {}
    virtual ~IField() {}

    std::string getName() const {
        return name_;
    }

protected:
    std::string name_;
};

// Int Field
class IntField : public IField {
public:
    IntField(const std::string& name, int* value)
        : IField(name), value_(value) {
    }

    // Specifics
    const int& getValue() const { return *value_; }
    void setValue(const int& value) { *value_ = value; }
    int* getRaw() { return value_; }

private:
    // Specifics
    int* value_;
};

// Char Field
class CharField : public IField {
public:
    CharField(const std::string& name, char* value)
        : IField(name), value_(value) {
    }

    // Specifics
    const char& getValue() const { return *value_; }
    void setValue(const char& value) { *value_ = value; }
    char* getRaw() { return value_; }

private:
    // Specifics
    char* value_;
};

// Float Field
class FloatField : public IField {
public:
    FloatField(const std::string& name, float* value)
        : IField(name), value_(value) {
    }

    // Specifics
    const float& getValue() const { return *value_; }
    void setValue(const float& value) { *value_ = value; }
    float* getRaw() { return value_; }

private:
    // Specifics
    float* value_;
};

// Bool Field
class BoolField : public IField {
public:
    BoolField(const std::string& name, bool* value)
        : IField(name), value_(value) {
    }

    // Specifics
    const bool& getValue() const { return *value_; }
    void setValue(const bool& value) { *value_ = value; }
    bool* getRaw() { return value_; }

private:
    // Specifics
    bool* value_;
};

// String Field
class StringField : public IField {
public:
    StringField(const std::string& name, std::string* value)
        : IField(name), value_(value) {
    }

    // Specifics
    const std::string& getValue() const { return *value_; }
    void setValue(const std::string& value) { *value_ = value; }
    std::string* getRaw() { return value_; }

private:
    // Specifics
    std::string* value_;
};

// Vector2D Field
class Vector2DField : public IField {
public:
    Vector2DField(const std::string& name, Vector2D* value)
        : IField(name), 
        x_("x", &value->x), 
        y_("y", &value->y) 
    {}

    // Specifics
    FloatField& getXField() { return x_; }
    FloatField& getYField() { return y_; }
    const FloatField& getXField() const { return x_; }
    const FloatField& getYField() const { return y_; }

private:
    // Specifics
    FloatField x_;
    FloatField y_;
};

// Transform2D Field
class Transform2DField : public IField {
public:
    Transform2DField(const std::string& name, Transform2D* value)
        : IField(name), 
        pos_("pos", &value->position), 
        scale_("scale", &value->scale),
        rotation_("rotation", &value->rotation),
        mirror_("mirror", &value->mirror),
        flip_("flip", &value->flip)
    {}

    // Specifics
    Vector2DField& getPosField() { return pos_; }
    Vector2DField& getScaleField() { return scale_; }
    FloatField& getRotationField() { return rotation_; }
    BoolField& getMirrorField() { return mirror_; }
    BoolField& getFlipField() { return flip_; }
    const Vector2DField& getPosField() const { return pos_; }
    const Vector2DField& getScaleField() const { return scale_; }
    const FloatField& getRotationField() const { return rotation_; }
    const BoolField& getMirrorField() const { return mirror_; }
    const BoolField& getFlipField() const { return flip_; }

private:
    // Specifics
    Vector2DField pos_;
    Vector2DField scale_;
    FloatField rotation_;
    BoolField mirror_;
    BoolField flip_;
};

#endif