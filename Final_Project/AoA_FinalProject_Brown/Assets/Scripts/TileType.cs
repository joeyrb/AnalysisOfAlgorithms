﻿using UnityEngine;
using System.Collections;
using System.Collections.Generic;

[System.Serializable]
public class TileType : MonoBehaviour {

    public string name;
    public GameObject tileVisualPrefab;

    public bool isWalkable = true;
    public float movementCost = 1;

}
