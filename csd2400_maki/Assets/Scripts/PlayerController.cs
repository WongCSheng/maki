using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class PlayerController : MonoBehaviour
{
    private PlayerMovement controls; //input system, No need do getkeydown as the script, PlayerMovement,
                                     //auto made by the input system, have all the get input stuff.

    public static Vector2 playerCurrentPoint;

    [SerializeField]
    private Tilemap groundTilemap; //get the groud Tilemap
    [SerializeField]
    private Tilemap wallTilemap; //get the wall Tilemap

    private GameObject[] objectToPush;

    private void Awake()
    {
        controls = new PlayerMovement(); //idk this... bring input system into this script?
    }

    private void OnEnable()
    {
        controls.Enable(); //enable it.
    }

    private void OnDisable()
    {
        controls.Disable(); //disable it.
    }

    // Start is called before the first frame update
    void Start()
    {
        controls.PlayerMovements.Move.performed += ctx => Move(ctx.ReadValue<Vector2>());

        objectToPush = GameObject.FindGameObjectsWithTag("PushableObjects"); //Find all the gameobjects with that tag
    }

    private void Move(Vector2 direction) //direction values is from input system. 
    {
        if (CanMove(direction)) //Player will move if CanMove == true
        {
            transform.position += (Vector3)direction;  //MOVE ME. - Player(2022)

            playerCurrentPoint = transform.position;
            Debug.Log(playerCurrentPoint);
        }
    }

    private bool CanMove(Vector2 direction) //direction values is Move function. 
    {
        Vector3Int gridPosition = groundTilemap.WorldToCell(transform.position + (Vector3)direction); //get the grid Position
        if (!groundTilemap.HasTile(gridPosition) || wallTilemap.HasTile(gridPosition)) //check if THERE IS NO tile on ground TM or THERE IS a tile on wall TM.
        {
            return false; //you hit a wall, player. STOP RIGHT THERE!
        }
        else { return true; } //you didn't hit a wall, player. You are allow to move.
    }

    // Update is called once per frame
    void Update()
    {

    }
}
