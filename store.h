#ifndef STORE_H_
#define STORE_H_


struct limits {
    signed char low;
};


void
limits_load(struct limits *l);


void
limits_save(struct limits *l);


#endif  // STORE_H_
