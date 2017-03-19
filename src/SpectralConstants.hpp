#ifndef SPECRALCONST_HPP
#define SPECRALCONST_HPP

// FIXME: This is NOT a thread safe way to do this.

namespace ModifiedSchwarz
{

/*!
 * Static class providing constructor constatns for spectral method.
 */
class SpectralConstants
{
    static bool _trapSet;
    static bool _truncSet;
    static unsigned _tmpTrapezoidalPoints;
    static unsigned _tmpSpectralTruncation;

    //! No public instances.
    SpectralConstants() {}

public:
    //! Number of collocation points for trapezoidal rule. Experiments have
    //! shown this to be a reasonable default value.
    constexpr static unsigned kDefaultTrapezoidalPoints = 100;

    //! Known good (via expermiment) default truncation level.
    constexpr static unsigned kDefaultSpectralTruncation = 96;

    /*!
     * Returns default number of trapezoidal points to use unless set was
     * called. If set was previously called, that value is cleared and next
     * call to this function will return defaults unless set is called again.
     */
    static unsigned kTrapezoidalPoints();

    /*!
     * Returns default truncation level for spectral method unless set was
     * called. If set was previously called, that value is cleared and next
     * call to this function will return defaults unless set is called again.
     */
    static unsigned kSpectralTruncation();

    /*!
     *  Sets value for next call of kTrapezoidalPoints(). Note SpectralMethod
     *  reads this constant on construction, and thus will undo any set call.
     */
    static void setTrapezoidalPoints(const unsigned trapezoidalPoints); //{ _tmpTrapezoidalPoints = trapezoidalPoints; }

    /*!
     *  Sets value for next call of kTrapezoidalPoints(). Note SpectralMethod
     *  reads this constant on construction, and thus will undo any set call.
     */
    static void setTruncation(const unsigned truncationLevel); //{ _tmpSpectralTruncation = truncationLevel; }
};

}; // ModifiedSchwarz

#endif // SPECRALCONST_HPP
