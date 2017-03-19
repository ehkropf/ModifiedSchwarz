#include "SpectralConstants.hpp"

namespace ModifiedSchwarz
{

bool SpectralConstants::_trapSet = false;
bool SpectralConstants::_truncSet = false;

unsigned SpectralConstants::_tmpTrapezoidalPoints = 0;
unsigned SpectralConstants::_tmpSpectralTruncation = 0;

unsigned
SpectralConstants::kTrapezoidalPoints()
{
    if (_trapSet)
    {
        _trapSet = false;
        return _tmpTrapezoidalPoints;
    }
    return kDefaultTrapezoidalPoints;
}

unsigned
SpectralConstants::kSpectralTruncation()
{
    if (_truncSet)
    {
        _truncSet = false;
        return _tmpSpectralTruncation;
    }
    return kDefaultSpectralTruncation;
}

void
SpectralConstants::setTrapezoidalPoints(const unsigned trapezoidalPoints)
{
    _tmpTrapezoidalPoints = trapezoidalPoints;
    _trapSet = true;
}

void
SpectralConstants::setTruncation(const unsigned truncationLevel)
{
    _tmpSpectralTruncation = truncationLevel;
    _truncSet = true;
}

}; // ModifiedSchwarz
