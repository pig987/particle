#include <raylib.h>
#include <vector>

using namespace std;


struct Particle{
    Vector2 position;
    Vector2 velocity;
    float lifespan;

    Particle(){
        position = {400, 225};
        velocity.x = float(GetRandomValue(-5, 5) * 0.1f);
        velocity.y = float(GetRandomValue(-5, 5) * 0.1f);
        lifespan = float(GetRandomValue(30, 35) * 0.1f);
    }

    virtual void Update(){
        lifespan -= 1.0f * GetFrameTime();
        position.x += velocity.x;
        position.y += velocity.y;
        DrawCircle(position.x, position.y, 10,BLACK);
    }
};

struct FireParticle : Particle{
    FireParticle(){
        position = {200, 225};
        velocity.x = float(GetRandomValue(-5, 5) * 0.1f);
        velocity.y = float(GetRandomValue(-10, -15) * 0.1f);
        lifespan = float(GetRandomValue(30, 35) * 0.1f);
    }

    void Update() override{
        lifespan -= 1.0f * GetFrameTime();
        position.x += velocity.x;
        position.y += velocity.y;
        DrawCircle(position.x, position.y, 5*lifespan, BLACK);
    }
};

struct SmokeParticle : Particle{
    SmokeParticle(){
        position = {600, 225};
        velocity.x = float(GetRandomValue(-5, 5) * 0.1f);
        velocity.y = float(GetRandomValue(-1, -5) * 0.1f);
        lifespan = float(GetRandomValue(30, 35) * 0.1f);
    }

    void Update() override{
        lifespan -= 1.0f * GetFrameTime();
        position.x += velocity.x;
        position.y += velocity.y;
        Color color = {0, 0, 0, 255};
        color.a = lifespan/3.0f * 255;
        DrawCircle(position.x, position.y, (4-lifespan)*5, color);
    }
};

vector<Particle*> particles;
float spawnTimer = 0.0f;

int main(){
    InitWindow(800, 450, "Particle App");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        spawnTimer += GetFrameTime();

        // 파티클 생성
        if(spawnTimer >= 0.05f){
            Particle* p = new SmokeParticle();
            particles.push_back(p);
            Particle* p2 = new FireParticle();
            particles.push_back(p2);
            spawnTimer = 0.0f;
        }

        for(auto& p: particles){
            if(p->lifespan > 0){
                p->Update();
            }
        }

        for(int i=particles.size()-1; i>=0; i--){
            if(particles[i]->lifespan <= 0){
                delete particles[i];
                particles.erase(particles.begin()+i);
            }
        }
        DrawText(TextFormat("Number of Particle: %i", particles.size()), 10, 10, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}