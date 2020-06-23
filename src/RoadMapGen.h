class RoadMap;

class RoadMapGen
{
public:
    RoadMapGen(RoadMap*);

    void generate();
private:
    RoadMap* roadMap;
};