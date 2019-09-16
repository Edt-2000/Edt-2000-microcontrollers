#pragma once

namespace App
{
enum class State
{
    begin = 1,
    networking = 2,
    specifics = 4,
    initialized = 8,
    run = 16
};
}