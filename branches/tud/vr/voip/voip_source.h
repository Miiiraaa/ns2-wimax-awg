/*
 * TODO: INSERT LICENSE HERE
 */

#ifndef __NS2_VOIP_SOURCE_H
#define __NS2_VOIP_SOURCE_H

#include <object.h>
#include <t_timers.h>

#include <ranvar.h>

class VoipEncoder;
class RandomVariable;

class VoipBidirectional;

class VoipSource : public TclObject {
public:
    //! Create an empty VoIP source.
    VoipSource ();

    //! Return true if the object is ready to be started.
    bool initialized () {
        return ( encoder_ && talk_ && silence_ ) || bidirectional_; }

    //! Tcl interface.
    /*!
         * Tcl commands:
         * - $obj debug\n
         *   Enable debug to standard error.
         * - $obj nodebug\n
         *   Disable debug to standard error (default).
         * - $obj start\n
         *   Start the first talkspurt generated by this VoIP source.
         * - $obj stop\n
         *   Do not generate any more talkspurts until resumed.
         * - $obj model exponential T S\n
         *   Draw the talkspurt and silence periods randomly from two
         *   exponential distributions with average T and S, respectively.
         * - $obj encoder $enc\n
         *   Bind the VoIP encoder $enc to this object $obj.
         * - $obj bidirectional $bidir\n
         *   Bind the VoIP bidirectional module $bidir to this object $obj.
         */
    virtual int command (int argc, const char*const* argv);

    //! Generate a new talkspurt.
    void handle ();

    //! Stops talkspurts generation
    void stop () {
        timer_.stop ();
    }

protected:
    //! Timer to schedule talkspurts.
    /*!
        * The timer is first started via a Tcl command.
        */
    TTimer<VoipSource> timer_;
    //! Pointer to the encoder application.
    VoipEncoder* encoder_;

    //! Pointer to the bidirectional module, if present.
    VoipBidirectional* bidirectional_;

    //! Random variable for talkspurt durations.
    RandomVariable* talk_;

    //! Random variable for silence durations.
    RandomVariable* silence_;

    WeibullRandomVariable talk1_;
    WeibullRandomVariable silence1_;

    //! Talkspurt counter.
    unsigned int count_;
    //! True if debug is enabled.
    bool debug_;
    bool stat_;
    int fid_;
};

#endif // __NS2_VOIP_SOURCE_H
