Welcome to Simple AVR's documentation!
======================================

Contents:

.. toctree::
   :maxdepth: 2

API
===

savr
----

.. c:macro:: SAVR_API_MAJOR 1

.. c:macro:: SAVR_API_MINOR 0

.. c:macro:: SAVR_API_PATCH 0

.. c:macro:: SAVR_API_VERSION "1.0.0"

.. c:macro:: SAVR_ABI_CUR 0

.. c:macro:: SAVR_ABI_REV 0

.. c:macro:: SAVR_ABI_AGE 0

.. c:macro:: SAVR_ABI_VERSION "0:0:0"

uart
----

.. c:function:: void uart_init(size_t buffer_size, int echo)

    Initialize the UART subsystem of the controller. The UART TX and RX pins
    will now be enabled, as well as the UART receive and transmit interrupts.
    Global interrupts will be unilateraly enabled too.

    :param size_t buffer_size: Size (in bytes) of the TX and RX ringbuffers.
    :param int echo: Enable echo from TX to RX.
    :rtype: void

.. c:function:: void uart_release()

    Release the UART capabilities of the controller.

    :type: void

.. c:function:: size_t uart_read(char* buffer, size_t size)

    Read characters from the RX queue.

    :param char* buffer: The buffer that will receive the read bytes.
    :param size_t size: The maximum number of bytes to read.
    :return: The number of bytes actually read.
    :rtype: size_t

.. c:function:: size_t uart_write(const char* buffer, unsigned int size)

    Write characters to the TX queue.

    :param buffer: The buffer from which characters will be sent.
    :type buffer: const char*
    :param size: Maximum number of characters to write.
    :type size: unsigned int
    :return: The number the bytes actually written.
    :rtype: size_t

ringbuffer
----------

.. c:function:: void ringbuffer_init(ringbuffer_t* rb, size_t size)

    Allocates memory for internal ringbuffer structures.

    :param ringbuffer_t* rb: The ringbuffer to initialize.
    :param size_t size: Size of the ringbuffer, in bytes.
    :rtype: void

.. c:function:: void ringbuffer_release(ringbuffer_t* rb)

    Releases memory allocated for internal ringbuffer structures.

    :param ringbuffer_t* rb: The ringbuffer to release.
    :rtype: void

.. c:function:: size_t ringbuffer_size(const ringbuffer_t* rb)

    Returns the size of the internal ringbuffer.

    :param rb: The ringbuffer on which to get the size.
    :type rb: const ringbuffer_t*
    :return: The size (in bytes) of the internal ring buffer.
    :rtype: size_t

.. c:function:: size_t ringbuffer_read(ringbuffer_t* rb, char* buffer, size_t size)

    Read from the ringbuffer to a buffer.

    :param ringbuffer_t* rb: The ringbuffer to read.
    :param char* buffer: The buffer where read bytes will be placed.
    :param size_t size: The maximum number of bytes to read and place in
                        ``buffer``.
    :return: The number of bytes actually read.
    :rtype: size_t

.. c:function:: size_t ringbuffer_write(ringbuffer_t* rb, const char* buffer, size_t size)

    Write to the ringbuffer from a buffer.

    :param ringbuffer_t* rb: The ringbuffer to write to.
    :param buffer: The input buffer to write.
    :type buffer: const char*
    :param size_t size: The maximum number of bytes to read from ``buffer`` and
                        write to the ringbuffer.
    :return: The number of bytes actually written.
    :rtype: size_t

.. c:function:: int ringbuffer_empty(const ringbuffer_t* rb)

    Returns whether the ringbuffer is presently empty.

    :param rb: The ringbuffer to test.
    :type rb: const ringbuffer_t*
    :return: ``1`` is the ringbuffer is empty, ``0`` otherwise.
    :rtype: int

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

