/**
 * @defgroup Hoversel Hoversel
 * @ingroup Elementary
 *
 * @image html hoversel_inheritance_tree.png
 * @image latex hoversel_inheritance_tree.eps
 *
 * @image html img/widget/hoversel/preview-00.png
 * @image latex img/widget/hoversel/preview-00.eps
 *
 * A hoversel is a button that pops up a list of items (automatically
 * choosing the direction to display) that have a label and, optionally, an
 * icon to select from. It is a convenience widget to avoid the need to do
 * all the piecing together yourself. It is intended for a small number of
 * items in the hoversel menu (no more than 8), though is capable of many
 * more.
 *
 * This widget inherits from the @ref Button one, so that all the
 * functions acting on it also work for hoversel objects.
 *
 * This widget emits the following signals, besides the ones sent from
 * @ref Button:
 * - @c "clicked" - the user clicked the hoversel button and popped up
 *   the sel
 * - @c "selected" - an item in the hoversel list is selected. event_info
 *   is the item
 * - @c "dismissed" - the hover is dismissed
 *
 * Default content parts of the hoversel widget that you can use for are:
 * @li "icon" - An icon of the hoversel
 *
 * Default text parts of the hoversel widget that you can use for are:
 * @li "default" - Label of the hoversel
 *
 * Supported elm_object common APIs.
 * @li @ref elm_object_disabled_set
 * @li @ref elm_object_disabled_get
 * @li @ref elm_object_part_text_set
 * @li @ref elm_object_part_text_get
 * @li @ref elm_object_part_content_set
 * @li @ref elm_object_part_content_unset
 *
 * Supported elm_object_item common APIs.
 * @li elm_object_item_part_text_get
 *
 * See @ref tutorial_hoversel for an example.
 * @{
 */

#define ELM_OBJ_HOVERSEL_CLASS elm_obj_hoversel_class_get()

const Eo_Class *elm_obj_hoversel_class_get(void) EINA_CONST;

extern EAPI Eo_Op ELM_OBJ_HOVERSEL_BASE_ID;

enum
{
   ELM_OBJ_HOVERSEL_SUB_ID_HOVER_PARENT_SET,
   ELM_OBJ_HOVERSEL_SUB_ID_HOVER_PARENT_GET,
   ELM_OBJ_HOVERSEL_SUB_ID_HORIZONTAL_SET,
   ELM_OBJ_HOVERSEL_SUB_ID_HORIZONTAL_GET,
   ELM_OBJ_HOVERSEL_SUB_ID_HOVER_BEGIN,
   ELM_OBJ_HOVERSEL_SUB_ID_HOVER_END,
   ELM_OBJ_HOVERSEL_SUB_ID_EXPANDED_GET,
   ELM_OBJ_HOVERSEL_SUB_ID_CLEAR,
   ELM_OBJ_HOVERSEL_SUB_ID_ITEMS_GET,
   ELM_OBJ_HOVERSEL_SUB_ID_ITEM_ADD,
   ELM_OBJ_HOVERSEL_SUB_ID_LAST
};

#define ELM_OBJ_HOVERSEL_ID(sub_id) (ELM_OBJ_HOVERSEL_BASE_ID + sub_id)


/**
 * @def elm_obj_hoversel_hover_parent_set
 * @since 1.8
 *
 * @brief Set the Hover parent
 *
 * @param[in] parent
 *
 * @see elm_hoversel_hover_parent_set
 */
#define elm_obj_hoversel_hover_parent_set(parent) ELM_OBJ_HOVERSEL_ID(ELM_OBJ_HOVERSEL_SUB_ID_HOVER_PARENT_SET), EO_TYPECHECK(Evas_Object *, parent)

/**
 * @def elm_obj_hoversel_hover_parent_get
 * @since 1.8
 *
 * @brief Get the Hover parent
 *
 * @param[out] ret
 *
 * @see elm_hoversel_hover_parent_get
 */
#define elm_obj_hoversel_hover_parent_get(ret) ELM_OBJ_HOVERSEL_ID(ELM_OBJ_HOVERSEL_SUB_ID_HOVER_PARENT_GET), EO_TYPECHECK(Evas_Object **, ret)

/**
 * @def elm_obj_hoversel_horizontal_set
 * @since 1.8
 *
 * @brief This sets the hoversel to expand horizontally.
 *
 * @param[in] horizontal
 *
 * @see elm_hoversel_horizontal_set
 */
#define elm_obj_hoversel_horizontal_set(horizontal) ELM_OBJ_HOVERSEL_ID(ELM_OBJ_HOVERSEL_SUB_ID_HORIZONTAL_SET), EO_TYPECHECK(Eina_Bool, horizontal)

/**
 * @def elm_obj_hoversel_horizontal_get
 * @since 1.8
 *
 * @brief This returns whether the hoversel is set to expand horizontally.
 *
 * @param[out] ret
 *
 * @see elm_hoversel_horizontal_get
 */
#define elm_obj_hoversel_horizontal_get(ret) ELM_OBJ_HOVERSEL_ID(ELM_OBJ_HOVERSEL_SUB_ID_HORIZONTAL_GET), EO_TYPECHECK(Eina_Bool *, ret)

/**
 * @def elm_obj_hoversel_hover_begin
 * @since 1.8
 *
 * @brief This triggers the hoversel popup from code, the same as if the user
 * had clicked the button.
 *
 *
 * @see elm_hoversel_hover_begin
 */
#define elm_obj_hoversel_hover_begin() ELM_OBJ_HOVERSEL_ID(ELM_OBJ_HOVERSEL_SUB_ID_HOVER_BEGIN)

/**
 * @def elm_obj_hoversel_hover_end
 * @since 1.8
 *
 * @brief This dismisses the hoversel popup as if the user had clicked
 * outside the hover.
 *
 *
 * @see elm_hoversel_hover_end
 */
#define elm_obj_hoversel_hover_end() ELM_OBJ_HOVERSEL_ID(ELM_OBJ_HOVERSEL_SUB_ID_HOVER_END)

/**
 * @def elm_obj_hoversel_expanded_get
 * @since 1.8
 *
 * @brief Returns whether the hoversel is expanded.
 *
 * @param[out] ret
 *
 * @see elm_hoversel_expanded_get
 */
#define elm_obj_hoversel_expanded_get(ret) ELM_OBJ_HOVERSEL_ID(ELM_OBJ_HOVERSEL_SUB_ID_EXPANDED_GET), EO_TYPECHECK(Eina_Bool *, ret)

/**
 * @def elm_obj_hoversel_clear
 * @since 1.8
 *
 * @brief This will remove all the children items from the hoversel.
 *
 *
 * @see elm_hoversel_clear
 */
#define elm_obj_hoversel_clear() ELM_OBJ_HOVERSEL_ID(ELM_OBJ_HOVERSEL_SUB_ID_CLEAR)

/**
 * @def elm_obj_hoversel_items_get
 * @since 1.8
 *
 * @brief Get the list of items within the given hoversel.
 *
 * @param[out] ret
 *
 * @see elm_hoversel_items_get
 */
#define elm_obj_hoversel_items_get(ret) ELM_OBJ_HOVERSEL_ID(ELM_OBJ_HOVERSEL_SUB_ID_ITEMS_GET), EO_TYPECHECK(const Eina_List **, ret)

/**
 * @def elm_obj_hoversel_item_add
 * @since 1.8
 *
 * @brief Add an item to the hoversel button
 *
 * @param[in] label
 * @param[in] icon_file
 * @param[in] icon_type
 * @param[in] func
 * @param[in] data
 * @param[out] ret
 *
 * @see elm_hoversel_item_add
 */
#define elm_obj_hoversel_item_add(label, icon_file, icon_type, func, data, ret) ELM_OBJ_HOVERSEL_ID(ELM_OBJ_HOVERSEL_SUB_ID_ITEM_ADD), EO_TYPECHECK(const char *, label), EO_TYPECHECK(const char *, icon_file), EO_TYPECHECK(Elm_Icon_Type, icon_type), EO_TYPECHECK(Evas_Smart_Cb, func), EO_TYPECHECK(const void *, data), EO_TYPECHECK(Elm_Object_Item **, ret)

/**
 * @brief Add a new Hoversel object
 *
 * @param parent The parent object
 * @return The new object or NULL if it cannot be created
 *
 * @ingroup Hoversel
 */
EAPI Evas_Object                 *elm_hoversel_add(Evas_Object *parent);

/**
 * @brief This sets the hoversel to expand horizontally.
 *
 * @param obj The hoversel object
 * @param horizontal If true, the hover will expand horizontally to the
 * right.
 *
 * @note The initial button will display horizontally regardless of this
 * setting.
 *
 * @ingroup Hoversel
 */
EAPI void                         elm_hoversel_horizontal_set(Evas_Object *obj, Eina_Bool horizontal);

/**
 * @brief This returns whether the hoversel is set to expand horizontally.
 *
 * @param obj The hoversel object
 * @return If true, the hover will expand horizontally to the right.
 *
 * @see elm_hoversel_horizontal_set()
 *
 * @ingroup Hoversel
 */
EAPI Eina_Bool                    elm_hoversel_horizontal_get(const Evas_Object *obj);

/**
 * @brief Set the Hover parent
 *
 * @param obj The hoversel object
 * @param parent The parent to use
 *
 * Sets the hover parent object, the area that will be darkened when the
 * hoversel is clicked. Should probably be the window that the hoversel is
 * in. See @ref Hover objects for more information.
 *
 * @ingroup Hoversel
 */
EAPI void                         elm_hoversel_hover_parent_set(Evas_Object *obj, Evas_Object *parent);

/**
 * @brief Get the Hover parent
 *
 * @param obj The hoversel object
 * @return The used parent
 *
 * Gets the hover parent object.
 *
 * @see elm_hoversel_hover_parent_set()
 *
 * @ingroup Hoversel
 */
EAPI Evas_Object                 *elm_hoversel_hover_parent_get(const Evas_Object *obj);

/**
 * @brief This triggers the hoversel popup from code, the same as if the user
 * had clicked the button.
 *
 * @param obj The hoversel object
 *
 * @ingroup Hoversel
 */
EAPI void                         elm_hoversel_hover_begin(Evas_Object *obj);

/**
 * @brief This dismisses the hoversel popup as if the user had clicked
 * outside the hover.
 *
 * @param obj The hoversel object
 *
 * @ingroup Hoversel
 */
EAPI void                         elm_hoversel_hover_end(Evas_Object *obj);

/**
 * @brief Returns whether the hoversel is expanded.
 *
 * @param obj The hoversel object
 * @return  This will return EINA_TRUE if the hoversel is expanded or
 * EINA_FALSE if it is not expanded.
 *
 * @ingroup Hoversel
 */
EAPI Eina_Bool                    elm_hoversel_expanded_get(const Evas_Object *obj);

/**
 * @brief This will remove all the children items from the hoversel.
 *
 * @param obj The hoversel object
 *
 * @warning Should @b not be called while the hoversel is active; use
 * elm_hoversel_expanded_get() to check first.
 *
 * @see elm_object_item_del()
 *
 * @ingroup Hoversel
 */
EAPI void                         elm_hoversel_clear(Evas_Object *obj);

/**
 * @brief Get the list of items within the given hoversel.
 *
 * @param obj The hoversel object
 * @return Returns a list of Elm_Object_Item*
 *
 * @see elm_hoversel_item_add()
 *
 * @ingroup Hoversel
 */
EAPI const Eina_List             *elm_hoversel_items_get(const Evas_Object *obj);

/**
 * @brief Add an item to the hoversel button
 *
 * @param obj The hoversel object
 * @param label The text label to use for the item (NULL if not desired)
 * @param icon_file An image file path on disk to use for the icon or standard
 * icon name (NULL if not desired)
 * @param icon_type The icon type if relevant
 * @param func Convenience function to call when this item is selected
 * @param data Data to pass to item-related functions
 * @return A handle to the item added.
 *
 * This adds an item to the hoversel to show when it is clicked. Note: if you
 * need to use an icon from an edje file then use
 * elm_hoversel_item_icon_set() right after this function, and set
 * icon_file to NULL here.
 *
 * For more information on what @p icon_file and @p icon_type are, see the
 * @ref Icon "icon documentation".
 *
 * @ingroup Hoversel
 */
EAPI Elm_Object_Item             *elm_hoversel_item_add(Evas_Object *obj, const char *label, const char *icon_file, Elm_Icon_Type icon_type, Evas_Smart_Cb func, const void *data);

/**
 * @brief This sets the icon for the given hoversel item.
 *
 * @param it The item to set the icon
 * @param icon_file An image file path on disk to use for the icon or standard
 * icon name
 * @param icon_group The edje group to use if @p icon_file is an edje file. Set this
 * to NULL if the icon is not an edje file
 * @param icon_type The icon type
 *
 * The icon can be loaded from the standard set, from an image file, or from
 * an edje file.
 *
 * @see elm_hoversel_item_add()
 *
 * @ingroup Hoversel
 */
EAPI void                         elm_hoversel_item_icon_set(Elm_Object_Item *it, const char *icon_file, const char *icon_group, Elm_Icon_Type icon_type);

/**
 * @brief Get the icon object of the hoversel item
 *
 * @param it The item to get the icon from
 * @param icon_file The image file path on disk used for the icon or standard
 * icon name
 * @param icon_group The edje group used if @p icon_file is an edje file. NULL
 * if the icon is not an edje file
 * @param icon_type The icon type
 *
 * @see elm_hoversel_item_icon_set()
 * @see elm_hoversel_item_add()
 *
 * @ingroup Hoversel
 */
EAPI void                         elm_hoversel_item_icon_get(const Elm_Object_Item *it, const char **icon_file, const char **icon_group, Elm_Icon_Type *icon_type);

/**
 * @}
 */
