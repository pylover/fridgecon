#ifndef STORE_H_
#define STORE_H_


struct limits {
    char magic;
    signed char low;
    signed char high;
};


void
limits_load(struct limits *l);


void
limits_save(struct limits *l);


#endif  // STORE_H_
