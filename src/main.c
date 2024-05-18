#include <stdio.h>
#include <stdlib.h>
#ifdef __linux__
#include <sys/mman.h>
#endif

struct Arena {
    unsigned int seats;
    void* head;
    void* pos;

};


struct Arena* constructArena(const size_t seats) {
#ifdef __linux__
    struct Arena* arena_ptr = mmap(NULL, seats + sizeof(struct Arena),
            PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE,
            -1, 0); 
#else
    struct Arena* arena_ptr = malloc(seats + sizeof(struct Arena)); 
#endif

    if (arena_ptr == NULL){
        return NULL;
    }

    arena_ptr->seats = seats;
    arena_ptr->head = (void*)(arena_ptr + 1);
    arena_ptr->pos = arena_ptr->head;

    return arena_ptr;
}


void* enterCombatant(struct Arena* arena, const unsigned int fighterGirth) {  
    if ((char*)arena->pos + fighterGirth > (char*)arena->head + arena->seats) {
        return NULL;
    }
    void* current = arena->pos;
    arena->pos = (void*)((char*)arena->pos + fighterGirth);
    return current;
}


// kills combatants!
void greyPrince(struct Arena* arena) {
    arena->pos = arena->head;
}


// kill everything! Does Skooma!
void heroOfKvatch(struct Arena* arena) {
    if (arena){
#ifdef __linux__
        munmap(arena, arena->seats);
#else
        free(arena);
#endif
    }
}


int main() {
    struct Arena* arena = constructArena(sizeof(char) * 4);
    if (arena == NULL) {
        printf("The Arena has failed!!");
        return 1;
    }

    char* x_ptr = (char*) enterCombatant(arena, 1);
    *x_ptr = 1;
    char* y_ptr = (char*) enterCombatant(arena, 1);
    *y_ptr = 2;
    char* z_ptr = (char*) enterCombatant(arena, 2);
    *z_ptr = 3;
    *(z_ptr + 1) = 4;

    for (int i = 0; i < 4; ++i) {
        printf("%d\n", *((char*)arena->head + i));
    }


    // this will fail.
    char* a_ptr = (char*) enterCombatant(arena, 1);
    if (a_ptr == NULL){
        printf("NO MOAR SEATS IN THE ARENA!\n");
    } else {printf("For this match we've got some fresh meat,....\n");}


    //"But who, you might ask, could possibly be brave enough to face such a 
    // fearless foe? Who could wrest the title from our famed Gray Prince?"
    greyPrince(arena);
    // Now it wont
    a_ptr = (char*) enterCombatant(arena, 1);
    if (a_ptr == NULL){
        printf("NO MOAR SEATS IN THE ARENA!\n");
    } else {printf("For this match we've got some fresh meat,....\n");}


    heroOfKvatch(arena); // rekt
    return 0;
}
