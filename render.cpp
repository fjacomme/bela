#include <Bela.h>
#include <libraries/Scope/Scope.h>

// instantiate the scope
Scope scope;

bool setup(BelaContext* context, void* userData)
{
    // tell the scope how many channels and the sample rate
    scope.setup(2, context->audioSampleRate);

    return true;
}

void render(BelaContext* context, void* userData)
{
    for (unsigned int n = 0; n < context->audioFrames; n++) {
        float out_l = audioRead(context, n, 0);
        float out_r = audioRead(context, n, 1);

        // log to the scope
        scope.log(out_l, out_r);
        scope.trigger();

        audioWrite(context, n, 0, out_l);
        audioWrite(context, n, 0, out_r);
    }
}

void cleanup(BelaContext* context, void* userData)
{
}