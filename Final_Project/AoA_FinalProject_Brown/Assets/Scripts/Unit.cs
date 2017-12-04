using UnityEngine;
using System.Collections;
using System.Collections.Generic;


public class Unit : MonoBehaviour {
    public int tileX;
    public int tiley;
    public TileMap map;

    public List<Node> currentPath = null;

    int moveSpeed = 2;

    void Start()
    {
        LineRenderer lineRenderer = gameObject.AddComponent<lineRenderer>();
        lineRenderer.material = new Material(Shader.Find("Particles/Additive"));
        lineRenderer.SetColors(Color.blue, Color.blue);
        lineRenderer.SetWidth(0.1F, 0.1F);
    }

    void Update()
    {
        if (currentPath != null)
        {
            LineRenderer lineRenderer = GetComponent<lineRenderer>();
            lineRenderer.SetVertexCount(currentPath.Count - 1);

            int currNode = 0;

            while(currNode < currentPath.Count - 1)
            {
                Vector3 start = map.TileCoordToWorldCoord(
                    currentPath[currNode].x, currentPath[currNode].y) +
                    new Vector3(0, 0, -1f);

                Vector3 end = map.TileCoordToWorldCoord(
                    currentPath[currNode + 1].x, currentPath[currNode + 1].y) +
                    new Vector3(0, 0, -1f);

                // Draw lines
                Debug.DrawLine(start, end, Color.red);      // debug view lines
                lineRenderer.SetPosition(currNode, end);    // game view lines

                currNode++;
            }
        }
    }

    public void MoveNextTile()
    {
        float remainingMovement = moveSpeed;

        while( remainingMovement > 0 )
        {
            if (currentPath == null)
                return;

            // Get cost between current tile to next tile
            remainingMovement -= map.CostToEnterTile(
                currentPath[0].x, currentPath[0].y, currentPath[1].y);

            // Move Unit to next tile in the sequence
            tileX = currentPath[1].x;   // update Unit's x-coordinate
            tiley = currentPath[1].y;   // update Unit's y-coordinate
            transform.position = map.TileCoordToWorldCoord(tileX, tiley); // update real world position


            // Remove old current tile
            currentPath.RemoveAt(0);

            if(currentPath.Count == 1)
            {
                currentPath = null; // initial current path -> done
            }
        }
    }




}
