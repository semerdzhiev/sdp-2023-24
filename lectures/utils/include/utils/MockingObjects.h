#pragma once

class NonCopiableDummy {
public:
    NonCopiableDummy() = default;
    NonCopiableDummy(const NonCopiableDummy&) = delete;
    NonCopiableDummy(NonCopiableDummy&&) = default;
};

class SingleNonCopiableParameterDummy {
public:
    explicit SingleNonCopiableParameterDummy(NonCopiableDummy param)
    {        
    }
};

class ConstructorSpy {
public:
    enum class ConstructorType {
        Default,
        Copy,
        Move
    };

    const ConstructorType constructedBy;

    ConstructorSpy() : constructedBy(ConstructorType::Default)
    {
    }

    ConstructorSpy(const ConstructorSpy&) : constructedBy(ConstructorType::Copy)
    {
    }

    ConstructorSpy(const ConstructorSpy&&) : constructedBy(ConstructorType::Move)
    {
    }
};
