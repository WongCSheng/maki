using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class Push : MonoBehaviour
{
    private Vector2 pushableObjectsCurrentPoint;
    private GameObject[] objectToPush;

    [SerializeField]
    private Tilemap groundTilemap; //get the groud Tilemap
    [SerializeField]
    private Tilemap wallTilemap; //get the wall Tilemap

    // Start is called before the first frame update
    void Start()
    {
        objectToPush = GameObject.FindGameObjectsWithTag("PushableObjects"); //Find all the gameobjects with that tag

        pushableObjectsCurrentPoint = transform.position;
        Debug.Log(pushableObjectsCurrentPoint);

        //Get player current point. [How to get?] (Done.)
        //If player current point = PushableObject point (Done.)
        //Move PushableObject point +/- up down left right depending on player current point [How to use Move only 1 block...]
        //So if Player current point is (1,0), PushableObject point is (0,0), Means player is on the right.
        //Player move into (0,0), Move PushableObject point to (-1,0).

        //if hit wall, Use CanMove(Vector2 direction)? Since CanMove() have the if statement to check if there's a wall infront a not...
    }

    // Update is called once per frame
    void Update()
    {
        if(PlayerController.playerCurrentPoint == pushableObjectsCurrentPoint)
        {
            Move(pushableObjectsCurrentPoint);
        }
    }

    private void Move(Vector2 direction)
    {
        if (CanMove(direction)) //move if CanMove == true
        {
            transform.position += (Vector3)direction;
        }
    }

    private bool CanMove(Vector2 direction) //direction values is Move function. 
    {
        Vector3Int gridPosition = groundTilemap.WorldToCell(transform.position + (Vector3)direction); //get the grid Position
        if (!groundTilemap.HasTile(gridPosition) || wallTilemap.HasTile(gridPosition)) //check if THERE IS NO tile on ground TM or THERE IS a tile on wall TM.
        {
            return false; //STOP RIGHT THERE!
        }
        else { return true; } //Go ahead. Move.
    }
}
