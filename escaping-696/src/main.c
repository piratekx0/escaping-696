#include "stdio.h"
#include "stdlib.h"
#include "raylib.h"
#include "raymath.h"
#include "string.h"
#include "math.h"
#include "time.h"
#include "linkedlist.h"

#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 960
#define NUMBER_OF_TEXTS 1

#define TEXT_SPEED 450.0f
#define M_KEY 77
#define TEXT_PADDING 2
#define COLLISION_MODIFIER 1

typedef struct {
    char *text;
    Vector2 position;
    Vector2 direction;
    int fontSize;
    Color color;
} CustomText;

typedef struct {
    struct Node node;
    CustomText customText;
    float timeAlive;
    float lifetime;
} TempText;

void CreateNewText(CustomText* location, CustomText props);
void CreateTempText(TempText* location, TempText props);
void UpdatePosition(CustomText* text, float speed, Vector2 direction, float delta);
void UpdateDirection(CustomText* text);

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TEST TITLE");
    SetTargetFPS(60);
    srand(time(NULL));
    
    CustomText *textArray = malloc(sizeof(CustomText) * NUMBER_OF_TEXTS);
    
    for (int i = 0; i < NUMBER_OF_TEXTS; i++) {
        CreateNewText(textArray + i, (CustomText){"dvd", {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {1, 1}, 100, WHITE});
    }
    
    struct Node* tempTextHead = createNode(1);
    
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        
        for (int j = 0; j < NUMBER_OF_TEXTS; j++) {
            CustomText *ptr = textArray + j;
            UpdatePosition(ptr, TEXT_SPEED, ptr->direction, delta);
            UpdateDirection(ptr);
        }
        
        if (IsKeyReleased(M_KEY)) {
            ToggleFullscreen();
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        
        for (int u = 0; u < NUMBER_OF_TEXTS; u++) {
            CustomText *ptr = textArray + u;
            DrawText(ptr->text, ptr->position.x, ptr->position.y, ptr->fontSize, ptr->color);
        }
        
        DrawFPS(GetScreenWidth() - 30, 10);
        //DrawText("Press 'M' to toggle fullscreen", 10, 10, 20, GREEN);
        
        EndDrawing();
    }
    
    free(textArray);
    CloseWindow();
}

void CreateNewText(CustomText* location, CustomText props) {
    location->text = props.text;
    location->position = props.position;
    location->direction = props.direction;
    location->fontSize = props.fontSize;
    location->color = props.color;
}

void CreateTempText(TempText* location, TempText props) {
    location->customText = props.customText;
    location->timeAlive = props.timeAlive;
    location->lifetime = props.lifetime;
}

void UpdatePosition(CustomText* text, float speed, Vector2 direction, float delta) {
    text->position.x += speed * direction.x * delta;
    text->position.y += speed * direction.y * delta;
}

void UpdateDirection(CustomText* text) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    
    int stringLength = strlen(text->text);
    int textLengthInPixels = (text->fontSize * stringLength + (stringLength * TEXT_PADDING)) / 2;
    int textHeightInPixels = text->fontSize;
    
    if (text->position.x > screenWidth - (textLengthInPixels / COLLISION_MODIFIER) || text->position.x < 0) {
        text->direction.x = (-text->direction.x);
    }
    
    if (text->position.y > screenHeight - textHeightInPixels || text->position.y < 0) {
        text->direction.y = (-text->direction.y);
    }
}