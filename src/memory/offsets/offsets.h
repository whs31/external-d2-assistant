#pragma once


struct Offsets
{
    Offsets() = default;
    struct Base
    {
        unsigned long long clientDll = 0;
        unsigned long long serverDll = 0;
    };




    static Base base;
};
Offsets::Base Offsets::base;

