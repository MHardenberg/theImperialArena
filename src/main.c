#include <stdio.h>
#include <stdlib.h>
#ifdef __linux__
#include <sys/mman.h>
#endif

struct Arena {
    size_t seats;
    void* head;
    void* pos;

};


struct Arena* constructArena(const size_t seats) {
    struct Arena* arena_ptr = malloc(sizeof(struct Arena));
    if (arena_ptr == NULL){
        // unable to alloc memory
        return NULL;
    }

#ifdef __linux__
     void* mem = mmap(NULL, seats + sizeof(struct Arena),
            PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE,
            -1, 0); 
     if (mem == MAP_FAILED) {goto cleanUpArena;}

#else
    // I don't care
    void* mem = malloc(seats + sizeof(struct Arena)); 
     if (mem == NULL) {goto cleanUpArena;}
#endif


    arena_ptr->seats = seats;
    arena_ptr->head = mem;
    arena_ptr->pos = arena_ptr->head;

    return arena_ptr;

cleanUpArena:
    free(arena_ptr);
    return NULL;
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
        munmap(arena->head, arena->seats);
        free(arena);
#else
        free(arena->head);
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

    char* x_ptr = (char*)enterCombatant(arena, 1);
    if (x_ptr != NULL) { *x_ptr = 1;}
    char* y_ptr = (char*)enterCombatant(arena, 1);
    if (y_ptr != NULL) {*y_ptr = 2;}
    char* z_ptr = (char*)enterCombatant(arena, 2);
    if (z_ptr != NULL) {
        *z_ptr = 3;
        *(z_ptr + 1) = 4;
    }

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
