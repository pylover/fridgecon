#ifndef HELPERS_H_
#define HELPERS_H_


#define MILI(v) (((long)v) * 1000)
#define SECOND(v) ((v) * 1000000)
#define MINUTE(m) SECOND((m) * 60)


enum {
    OFF = 0,
    NO = 0,
    ON = 1,
    YES = 1,
};


#endif  // HELPERS_H_
