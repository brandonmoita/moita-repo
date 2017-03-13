using UnityEngine;
using UnityEngine.UI;
using System.Collections;


[RequireComponent(typeof(CharacterController))]
public class Character2 : MonoBehaviour
{


    public float speed = 6.0f;
    public float jumpSpeed = 8.0f;
    public float rotateSpeed = 5.0f;
    public float gravity = 9.81f;
    Vector3 moveDirection = Vector3.zero;

    public int type = 0;

    private int count2;
    public Text countText2;

    CharacterController cc;

    public Rigidbody projectilePrefab;
    public Transform projectileSpawnPoint;
    public float fireSpeed = 50.0f;

    // Use this for initialization
    void Start()
    {
        //Grab a component and keep a reference to it
        cc = GetComponent<CharacterController>();
        if (!cc)
            Debug.Log("CharacterController does not exist.");

        count2 = 0;
        SetCountText2();


    }

    // Update is called once per frame
    void Update()
    {
        //SimpleMove()
        if (type == 1)
        {
            transform.Rotate(0, Input.GetAxis("Horizontal2") * rotateSpeed, 0);

            Vector3 forward = transform.TransformDirection(Vector3.forward);

            float curSpeed = speed * Input.GetAxis("Vertical2");

            cc.SimpleMove(forward * curSpeed);
        }
        //Move()
        else if (type == 0)
        {
            if (cc.isGrounded)
            {
                moveDirection = new Vector3(0, 0, Input.GetAxis("Vertical2"));

                transform.Rotate(0, Input.GetAxis("Horizontal2") * rotateSpeed, 0);

                moveDirection = transform.TransformDirection(moveDirection);

                moveDirection *= speed;

                //jump function

                if (Input.GetButtonDown("Jump2"))
                    moveDirection.y = jumpSpeed;

            }

            moveDirection.y -= gravity * Time.deltaTime;

            cc.Move(moveDirection * Time.deltaTime);
        }

        //Key Press Stuff
        if (Input.GetButtonDown("Fire1"))
        {
            Debug.Log("Down Fire!!");
            if (projectilePrefab)
            {
                Rigidbody temp = Instantiate(projectilePrefab, projectileSpawnPoint.position, projectileSpawnPoint.rotation) as Rigidbody;

                temp.AddForce(projectileSpawnPoint.transform.forward * fireSpeed, ForceMode.Impulse);
            }
            else
                Debug.Log("No PreFab found");

        }

        if (Input.GetButtonUp("Fire1"))
        {
            Debug.Log("Up Fire!!");
        }

        if (Input.GetKeyDown(KeyCode.LeftControl))
        {

        }



        //Check CollisionFlags on CharacterController
        if (cc.collisionFlags == CollisionFlags.None)
        {
            Debug.Log("Character in air.");
        }

    } //Update


    //Needs Collider Attached to GameObject

    void OnTriggerEnter(Collider other)
    {

        if (other.gameObject.tag == "PickUp")
        {
            Destroy(other.gameObject);
            count2 = count2 + 50;
            SetCountText2();

        }

        Debug.Log("Tigger Happened");
    }



    void SetCountText2()

    {

        countText2.text = "Score: " + count2.ToString();

    }
}



