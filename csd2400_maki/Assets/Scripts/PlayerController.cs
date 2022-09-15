using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class PlayerController : MonoBehaviour
{
    private PlayerMovement controls; //input system, No need do getkeydown as the script, PlayerMovement,
                                     //auto made by the input system, have all the get input stuff.

    [SerializeField]
    private Tilemap groundTilemap; //get the groud Tilemap
    [SerializeField]
    private Tilemap wallTilemap; //get the wall Tilemap

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
        //movePoint.parent = null; //movePoint no more parent using script
    }

    private void Move(Vector2 direction)
    {
        if (CanMove(direction))
        {
            transform.position += (Vector3)direction;
        }
    }

    private bool CanMove(Vector2 direction)
    {
        Vector3Int gridPosition = groundTilemap.WorldToCell(transform.position + (Vector3)direction);
        if (!groundTilemap.HasTile(gridPosition) || wallTilemap.HasTile(gridPosition))
        {
            return false;
        }
        else { return true; }
    }

    // Update is called once per frame
    void Update()
    {

    }
}
