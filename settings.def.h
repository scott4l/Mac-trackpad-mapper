#pragma once

// Do not remove this. This variable is initialized in main program
extern CGSize screenSize;
// Emit mouse event or wrap cursor. Default is warp cursor
bool emitMouseEvent = false;

// Helper function: lower and upper has to be without 0 to 1 inclusive
static inline double rangeRatio(double n, double lower, double upper) {
    if (n < lower || n > upper) {
        return -1;
    }
    return (n - lower) / (upper - lower);
}

// Compulsory: Modify this function to change how relative position of trackpad is mapped to normalized screen coordinates. Return negative number for invalid finger position
static inline MTPoint map(double normx, double normy) {
    // 0.25 to 0.75 restricts input to the center 50% of your touchpad
    double rx = rangeRatio(normx, 0.25, 0.75);
    double ry = rangeRatio(normy, 0.25, 0.75);

    // Ignore finger touches outside the small area
    if (rx < 0 || ry < 0) {
        MTPoint invalidPoint = { .x = -1.0, .y = -1.0 };
        return invalidPoint;
    }

    // Scale the small active area to reach the entire screen
    MTPoint point = {
        .x = rx * screenSize.width,
        .y = ry * screenSize.height,
    };
    return point;
}


// Jitter / smoothing settings for absolute cursor mode
static const double JITTER_THRESHOLD = 4.0;  // in screen pixels (try 4–10)

// Smoothing factor for cursor motion (0..1).
// If set to 0, it will be clamped to 0.1 in trackpad_mapper_util.c to avoid the cursor getting stuck.
static const double JITTER_ALPHA = 0.6;

// Disable custom cursor movement whenever more than one finger is on the pad
static const bool DISABLE_CURSOR_ON_MULTITOUCH = true;
