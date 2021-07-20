#include "SceneRenderer.h"

#include "TileMap.h"
#include "tileMapUtil.h"
#include "Scene.h"
#include "Renderer.h"
#include "generator/bottomuprectplacer.h"


#include "SquareEntity.h"
#include "util/Random.h"

class Pig: public SquareEntity {};
class Player: public SquareEntity {};
class Truck: public Entity {};

TexId pigTex;
TexId playerTex;
TexId truckTex;
TexId winTex;
TexId roadTex;
TexId forestTex;

static constexpr glm::vec3 NO_ROAD_COLOR(0.35f, 0.59f, 0.6f);


inline Color getRandomColor()
{
    static auto ranCh = []() {return Random::get()->ranFloat(1.0f, 255); };
    return Color(ranCh(), ranCh(), ranCh());
}

SceneRenderer::SceneRenderer(const Scene& scene)
    : scene(scene), tileMap(*scene.getRoadMap()), getHouseColor([] (int x) {return getRandomColor();})
{
    pigTex = Renderer::get()->initTexture("res/textures/cartoonpig.jpeg");
    playerTex = Renderer::get()->initTexture("res/textures/awesome-face.jpeg");
    truckTex = Renderer::get()->initTexture("res/textures/truck.jpeg");
    winTex = Renderer::get()->initTexture("res/textures/you-win.jpeg");
    roadTex = Renderer::get()->initTexture("res/textures/road.png");
    forestTex = Renderer::get()->initTexture("res/textures/forest.jpeg");
}

SceneRenderer::~SceneRenderer()
{
}

void initDrawHouse(const Color& color)
{
    //Renderer::get()->setFillColor(Color(1.f, 1.f, 0.f));
    //Renderer::get()->setChromaKeyEnable(true);
    //Renderer::get()->setChromaKey(color);
    Renderer::get()->setFillColor(color);
}

void SceneRenderer::drawTileMap()
{
    auto& renderer = *Renderer::get();
    renderer.setFillTexture(roadTex);
    for (int x = 0; x < tileMap.getWidth(); x++)
    {
        for (int y = 0; y < tileMap.getHeight() ; y++)
        {
            //set color white by default
            auto coord = glm::vec2i(x, y);
            auto state = tileMap.getTileState(coord);

            if (state == NO_ROAD)
                renderer.setFillColor(NO_ROAD_COLOR);
            else if (state == HOUSE)
            {
                initDrawHouse(getHouseColor(pos2Index(tileMap.getWidth(), coord)));
            } else if (isRoad(state)){
                renderer.setFillTexture(roadTex);
                renderer.rotateTexture(state == HORIZONTAL ? CompassDirection::WEST : CompassDirection::NORTH);
            } else {
                continue;
            }

            Renderer::get()->drawSquare(coord, 1.0f);
        }

    }
}

void drawEntity(Entity& entity) // TODO Entity constness
{
    Renderer::get()->drawRectangle(entity.getPos(), entity.getDims());
}

void SceneRenderer::render ()
{
    auto& renderer = *Renderer::get();
    renderer.activate();

    //draw forest
    renderer.setWorldCoords(false);
    renderer.setFillTexture(forestTex);
    renderer.drawBackground(glm::vec2(1.f));

    renderer.setWorldCoords(true);
    drawTileMap();
    auto& player = *scene.player;
    auto& pigs = const_cast<std::vector<Pig>&>(scene.pigs); //TODO this is an abomination!
    Truck& truck = *scene.truck;

    renderer.rotateTexture(CompassDirection::NORTH);
    //draw player
    renderer.setFillTexture(playerTex);
    renderer.drawSquare(player.getPos(), player.getWidth());

    //draw pigs
    auto drawPig = [&renderer, this] (SquareEntity& p)
    {
        renderer.drawSquare(p.getPos(), p.getWidth());
    };

    renderer.setFillTexture(pigTex);
    for (auto& pig: pigs) drawPig(pig);

    //draw truck
    renderer.setFillTexture(truckTex);
    drawEntity(truck);

    if (scene.isWon()) {
        renderer.setWorldCoords(false);
        renderer.setFillTexture(winTex);
        renderer.drawSquare(RealPos(-0.5f, -0.5f), 1.f);
    }

}

const RealPos& Scene::getPlayerPos() {
    return player->getPos();
}
