using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

public class TileMap : MonoBehaviour {

    public GameObject selectedUnit;

    public TileType[] tileTypes;

    int[,] tiles;
    Node[,] graph;

    int mapSizeX = 10;
    int mapSizeY = 10;

    void Start()
    {
        // Setup the selectedUnit's variables
        selectedUnit.GetComponent<Unit>().tileX = (int)selectedUnit.transform.position.x;
        selectedUnit.GetComponent<Unit>().tileY = (int)selectedUnit.transform.position.y;
        selectedUnit.GetComponent<Unit>().map = this;
        GenerateMapData();
        GeneratePathfindingGraph();
        GenerateMapVisual();

        // allocate map tiles
        tiles = new int[mapSizeX, mapSizeY];

        // initialize map tiles to grass
        for (int x = 0; x < mapSizeX; ++x) {
            for (int y = 0; y < mapSizeY; ++y) {
                tiles[x, y] = 0;
            }
        }

        // U-shaped mountain range
        tiles[4, 4] = 2;
        tiles[5, 4] = 2;
        tiles[6, 4] = 2;
        tiles[7, 4] = 2;
        tiles[8, 4] = 2;

        tiles[4, 5] = 2;
        tiles[4, 6] = 2;
        tiles[8, 5] = 2;
        tiles[8, 6] = 2;

        // Spawn visual prefabs
        GenerateMapVisual();
    }

    void GenerateMapData()
    {
        // Map tile allocation
        tiles = new int[mapSizeX, mapSizeY];

        int x, y;   // 2D coordinates

        // Initialize map tiles as Grass
        for (x = 0; x < mapSizeX; ++x)
        {
            for (y = 0; y < mapSizeX; ++y)
            {
                tiles[x, y] = 0;
            }
        }

        // Create Swamp
        for (x = 3; x <= 5; ++x)
        {
            for (y = 0; y < 4; ++y)
            {
                tiles[x, y] = 1;
            }
        }

        // Create Mountain
        tiles[4, 4] = 2;
        tiles[5, 4] = 2;
        tiles[6, 4] = 2;
        tiles[7, 4] = 2;
        tiles[8, 4] = 2;
        tiles[4, 5] = 2;
        tiles[4, 6] = 2;
        tiles[8, 5] = 2;
        tiles[8, 6] = 2;
    }

    // Gives Cost to tiles
    public float CostToEnterTile(int sourceX, int sourceY, int targetX, int targetY)
    {
        TileType tt = tileTypes[tiles[targetX, targetY]]; 

        if(UnitCanEnterTile(targetX, targetY) == false)
        {
            return Mathf.Infinity;
        }

        float cost = tt.movementCost;

        if(sourceX != targetX && sourceY != targetY)
        {
            // tie breaking diagonal movement
            cost += 0.001f;
        }

        return cost;
    }

    // Generate Node Network
    void GeneratePathfindingGraph()
    {
        // Initialize Node array
        graph = new Node[mapSizeX, mapSizeY];

        // Initialize each Node in the array 
        for(int x = 0; x < mapSizeX; ++x)
        {
            for(int y = 0; y < mapSizeX; ++y)
            {
                graph[x, y] = new Node();
                graph[x, y].x = x;
                graph[x, y].y = y;
            }
        }

        // Calculate neighbors of Nodes
        for(int x = 0; x < mapSizeX; ++x)
        {
            for(int y = 0; y < mapSizeX; ++y)
            {
                /*// 4-way connected map
                if (x > 0)
                    graph[x, y].neighbours.Add(graph[x - 1, y]);
                if (x < mapSizeX - 1)
                    graph[x, y].neighbours.Add(graph[x + 1, y]);
                if (y > 0)
                    graph[x, y].neighbours.Add(graph[x, y - 1]);
                if (y < mapSizeY - 1)
                    graph[x, y].neighbours.Add(graph[x, y + 1]);
                */
                
                // 8-way connected map (allows for diagonal movement)
                // Try LEFT
                if (x > 0)
                {
                    graph[x, y].neighbours.Add(graph[x - 1, y]);
                    if (y > 0)
                        graph[x, y].neighbours.Add(graph[x - 1, y - 1]);
                    if (y < mapSizeY - 1)
                        graph[x, y].neighbours.Add(graph[x - 1, y + 1]);
                }
                // Try RIGHT
                if (x < mapSizeX - 1)
                {
                    graph[x, y].neighbours.Add(graph[x + 1, y]);
                    if (y > 0)
                        graph[x, y].neighbours.Add(graph[x + 1, y - 1]);
                    if (y < mapSizeY - 1)
                        graph[x, y].neighbours.Add(graph[x + 1, y + 1]);
                }
                // Try directly DOWN
                if (y > 0)
                    graph[x, y].neighbours.Add(graph[x, y - 1]);
                if (y < mapSizeY - 1)
                    graph[x, y].neighbours.Add(graph[x, y + 1]);
            }
        }


    }

    void GenerateMapVisual()
    {
        for(int x=0; x < mapSizeX; ++x) {
            for(int y=0; y < mapSizeY; ++y) {
                TileType tt = tileTypes[ tiles[x,y] ];
                GameObject go = (GameObject)Instantiate(
                    tt.tileVisualPrefab,
                    new Vector3(x, y, 0),
                    Quaternion.identity);
                ClickableTile ct = go.GetComponent<ClickableTile>();
                ct.tileX = x;
                ct.tileY = y;
                ct.map = this;
            }
        }
    }
}
