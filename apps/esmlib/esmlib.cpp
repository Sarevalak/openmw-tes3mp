#include "esmlib.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include "esm/esmcommon.hpp"
#include "esm/loadtes3.hpp"
#include "esm/esmreader.hpp"
#include "esm/loadalch.hpp"
#include "esm/effectlist.hpp"
#include "esm/loadacti.hpp"
#include "esm/loadappa.hpp"
#include "esm/loadarmo.hpp"
#include "esm/loadland.hpp"
#include "esm/loadmgef.hpp"
#include "esm/loaddoor.hpp"
#include "esm/loadbook.hpp"
#include "esm/cellid.hpp"
#include "esm/variant.hpp"
#include "esm/loadstat.hpp"
#include "esm/loadspel.hpp"
#include "esm/loadskil.hpp"
#include "esm/loadmisc.hpp"
#include "esm/loadltex.hpp"
#include "esm/loadingr.hpp"
#include "esm/loadglob.hpp"
#include "esm/loadench.hpp"
#include "esm/loadcrea.hpp"
#include "esm/loadcont.hpp"
#include "esm/loadclot.hpp"
#include "esm/loadclas.hpp"
#include "esm/loadbsgn.hpp"
#include "esm/loadbody.hpp"
#include "esm/transport_dest.hpp"

using namespace luabridge;

void register_esmlib(lua_State* L) {
    luabridge::getGlobalNamespace(L)
        .beginNamespace("ESM")

        .beginClass<ESM::LESMReader>("ESMReader")
        .addConstructor<void (*)()>()
        .addFunction("getVer", &ESM::LESMReader::getVer)
        .addFunction("getRecordCount", &ESM::LESMReader::getRecordCount)
        .addFunction("getFVer", &ESM::LESMReader::getFVer)
        .addFunction("getAuthor", &ESM::LESMReader::getAuthor)
        .addFunction("getDesc", &ESM::LESMReader::getDesc)
        .addCFunction("getGameFiles", &ESM::LESMReader::getGameFiles)
        .addFunction("getHeader", &ESM::LESMReader::getHeader)
        .addFunction("getFormat", &ESM::LESMReader::getFormat)
        .addFunction("retSubName", &ESM::LESMReader::retSubName)
        .addFunction("getSubSize", &ESM::LESMReader::getSubSize)
        .addFunction("getName", &ESM::LESMReader::getName)
        .addFunction("getContext", &ESM::LESMReader::getContext)
        .addFunction("restoreContext", &ESM::LESMReader::restoreContext)
        .addFunction("open", &ESM::LESMReader::open)
        .addFunction("close", &ESM::LESMReader::close)
        .addFunction("getFileOffset", &ESM::LESMReader::getFileOffset)
        .addFunction("setIndex", &ESM::LESMReader::setIndex)
        .addFunction("getIndex", &ESM::LESMReader::getIndex)
        // .addFunction("setGlobalReaderList", &ESM::LESMReader::setGlobalReaderList)
        // .addFunction("getGlobalReaderList", &ESM::LESMReader::getGlobalReaderList)
        .addFunction("getRecName", &ESM::LESMReader::getRecName)
        .addFunction("skipRecord", &ESM::LESMReader::skipRecord)
        .addFunction("getRecHeader", &ESM::LESMReader::getRecHeader)
        .addFunction("hasMoreRecs", &ESM::LESMReader::hasMoreRecs)
        .addFunction("hasMoreSubs", &ESM::LESMReader::hasMoreSubs)
        .addFunction("getRecordFlags", &ESM::LESMReader::getRecordFlags)
        .addFunction("getFileSize", &ESM::LESMReader::getFileSize)
        .endClass()

        .beginClass<ESM::LHeader>("Header")
        .addConstructor<void (*)()>()
        .addProperty("CurrentFormat", &ESM::LHeader::getCurrentFormat)
        .endClass()

        .beginClass<ESM::LMasterData>("MasterData")
        .addConstructor<void (*)()>()
        .addProperty("name", &ESM::LMasterData::getName)
        .addProperty("size", &ESM::LMasterData::getSize)
        .addProperty("index", &ESM::LMasterData::getIndex)
        .endClass()

        .beginClass<ESM::LESM_Context>("ESM_Context")
        .addConstructor<void (*)()>()
        .addProperty("filename", &ESM::LESM_Context::getFilename)
        .addProperty("leftRec", &ESM::LESM_Context::getLeftRec)
        .addProperty("leftSub", &ESM::LESM_Context::getLeftSub)
        .addProperty("leftFile", &ESM::LESM_Context::getLeftFile)
        .addProperty("recName", &ESM::LESM_Context::getRecName)
        .addProperty("subName", &ESM::LESM_Context::getSubName)
        .addProperty("index", &ESM::LESM_Context::getIndex)
        .addProperty("subCached", &ESM::LESM_Context::getSubCached)
        .addProperty("filePos", &ESM::LESM_Context::getFilePos)
        .endClass()

        .beginClass<ESM::LPotion>("Potion")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LPotion::getRecordId)
        .addProperty("recordType", &ESM::LPotion::getRecordType)
        .addProperty("weight", &ESM::LPotion::getWeight)
        .addProperty("value", &ESM::LPotion::getValue)
        .addProperty("autoCalc", &ESM::LPotion::getAutoCalc)
        .addProperty("id", &ESM::LPotion::getId)
        .addProperty("name", &ESM::LPotion::getName)
        .addProperty("model", &ESM::LPotion::getModel)
        .addProperty("icon", &ESM::LPotion::getIcon)
        .addProperty("script", &ESM::LPotion::getScript)
        .addCFunction("effects", &ESM::LPotion::getEffects)
        .addFunction("load", &ESM::LPotion::load)
        .endClass()

        .beginClass<ESM::LENAMstruct>("ENAMstruct")
        .addConstructor<void (*)()>()
        .addProperty("effectID", &ESM::LENAMstruct::getEffectID)
        .addProperty("skill", &ESM::LENAMstruct::getSkill)
        .addProperty("attribute", &ESM::LENAMstruct::getAttribute)
        .addProperty("range", &ESM::LENAMstruct::getRange)
        .addProperty("area", &ESM::LENAMstruct::getArea)
        .addProperty("duration", &ESM::LENAMstruct::getDuration)
        .addProperty("magnMin", &ESM::LENAMstruct::getMagnMin)
        .addProperty("magnMax", &ESM::LENAMstruct::getMagnMax)
        .endClass()

        .beginClass<ESM::LActivator>("Activator")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LActivator::getRecordId)
        .addProperty("recordType", &ESM::LActivator::getRecordType)
        .addProperty("id", &ESM::LActivator::getId)
        .addProperty("name", &ESM::LActivator::getName)
        .addProperty("model", &ESM::LActivator::getModel)
        .addProperty("script", &ESM::LActivator::getScript)
        .addFunction("load", &ESM::LActivator::load)
        .endClass()

        .beginClass<ESM::LApparatus>("Apparatus")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LApparatus::getRecordId)
        .addProperty("recordType", &ESM::LApparatus::getRecordType)
        .addProperty("id", &ESM::LApparatus::getId)
        .addProperty("name", &ESM::LApparatus::getName)
        .addProperty("model", &ESM::LApparatus::getModel)
        .addProperty("icon", &ESM::LApparatus::getIcon)
        .addProperty("script", &ESM::LApparatus::getScript)
        .addProperty("type", &ESM::LApparatus::getType)
        .addProperty("quality", &ESM::LApparatus::getQuality)
        .addProperty("weight", &ESM::LApparatus::getWeight)
        .addProperty("value", &ESM::LApparatus::getValue)
        .addFunction("load", &ESM::LApparatus::load)
        .endClass()

        .beginClass<ESM::LPartReference>("PartReference")
        .addConstructor<void (*)()>()
        .addProperty("part", &ESM::LPartReference::getPart)
        .addProperty("male", &ESM::LPartReference::getMale)
        .addProperty("female", &ESM::LPartReference::getFemale)
        .endClass()

        .beginClass<ESM::LArmor>("Armor")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LArmor::getRecordId)
        .addProperty("recordType", &ESM::LArmor::getRecordType)
        .addProperty("id", &ESM::LArmor::getId)
        .addProperty("name", &ESM::LArmor::getName)
        .addProperty("model", &ESM::LArmor::getModel)
        .addProperty("icon", &ESM::LArmor::getIcon)
        .addProperty("script", &ESM::LArmor::getScript)
        .addProperty("enchantId", &ESM::LArmor::getEnchantId)
        .addProperty("type", &ESM::LArmor::getType)
        .addProperty("weight", &ESM::LArmor::getWeight)
        .addProperty("value", &ESM::LArmor::getValue)
        .addProperty("health", &ESM::LArmor::getHealth)
        .addProperty("enchant", &ESM::LArmor::getEnchant)
        .addProperty("armor", &ESM::LArmor::getArmor)
        .addCFunction("parts", &ESM::LArmor::getParts)
        .addFunction("load", &ESM::LArmor::load)
        .endClass()

        .beginClass<ESM::LLandData>("LandData")
        .addConstructor<void (*)()>()
        .addProperty("heightOffset", &ESM::LLandData::getHeightOffset)
        .addCFunction("heights", &ESM::LLandData::getHeights)
        .addProperty("minHeight", &ESM::LLandData::getMinHeight)
        .addProperty("maxHeight", &ESM::LLandData::getMaxHeight)
        .addCFunction("textures", &ESM::LLandData::getTextures)
        .addProperty("dataLoaded", &ESM::LLandData::getDataLoaded)
        .endClass()

        .beginClass<ESM::LLand>("Land")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LLand::getRecordId)
        .addProperty("recordType", &ESM::LLand::getRecordType)
        .addProperty("flags", &ESM::LLand::getFlags)
        .addProperty("x", &ESM::LLand::getX)
        .addProperty("y", &ESM::LLand::getY)
        .addProperty("plugin", &ESM::LLand::getPlugin)
        .addFunction("getContext", &ESM::LLand::getContext)
        .addFunction("setContext", &ESM::LLand::setContext)
        .addProperty("dataTypes", &ESM::LLand::getDataTypes)
        .addFunction("availableData", &ESM::LLand::getAvailableData)
        .addFunction("load", &ESM::LLand::load)
        .addFunction("unloadData", &ESM::LLand::unloadData)
        .addFunction("isDataLoaded", &ESM::LLand::isDataLoaded)
        .addFunction("loadData", &ESM::LLand::loadData)
        // .addFunction("setDataLoaded", &ESM::LLand::setDataLoaded)
        .addFunction("getLandData", &ESM::LLand::getLandData)
        .endClass()

        .beginClass<ESM::LMagicEffect>("MagicEffect")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LMagicEffect::getRecordId)
        .addProperty("recordType", &ESM::LMagicEffect::getRecordType)
        .addProperty("id", &ESM::LMagicEffect::getId)
        .addFunction("effectIdToString", &ESM::LMagicEffect::effectIdToString)
        .addFunction("effectStringToId", &ESM::LMagicEffect::effectStringToId)
        .addFunction("getResistanceEffect", &ESM::LMagicEffect::getResistanceEffect)
        .addFunction("getWeaknessEffect", &ESM::LMagicEffect::getWeaknessEffect)
        .addFunction("indexToId", &ESM::LMagicEffect::indexToId)
        .addProperty("magnitudeDisplayType", &ESM::LMagicEffect::getMagnitudeDisplayType)
        .addProperty("hit", &ESM::LMagicEffect::getHit)
        .addProperty("area", &ESM::LMagicEffect::getArea)
        .addProperty("casting", &ESM::LMagicEffect::getCasting)
        .addProperty("icon", &ESM::LMagicEffect::getIcon)
        .addProperty("particle", &ESM::LMagicEffect::getParticle)
        .addProperty("bolt", &ESM::LMagicEffect::getBolt)
        .addProperty("castSound", &ESM::LMagicEffect::getCastSound)
        .addProperty("boltSound", &ESM::LMagicEffect::getBoltSound)
        .addProperty("hitSound", &ESM::LMagicEffect::getHitSound)
        .addProperty("areaSound", &ESM::LMagicEffect::getAreaSound)
        .addProperty("description", &ESM::LMagicEffect::getDescription)
        .addProperty("index", &ESM::LMagicEffect::getIndex)
        .addProperty("school", &ESM::LMagicEffect::getSchool)
        .addProperty("baseCost", &ESM::LMagicEffect::getBaseCost)
        .addProperty("flags", &ESM::LMagicEffect::getFlags)
        .addProperty("red", &ESM::LMagicEffect::getRed)
        .addProperty("green", &ESM::LMagicEffect::getGreen)
        .addProperty("blue", &ESM::LMagicEffect::getBlue)
        .addFunction("load", &ESM::LMagicEffect::load)
        .endClass()

        .beginClass<ESM::LDoor>("Door")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LDoor::getRecordId)
        .addProperty("recordType", &ESM::LDoor::getRecordType)
        .addProperty("id", &ESM::LDoor::getId)
        .addProperty("name", &ESM::LDoor::getName)
        .addProperty("model", &ESM::LDoor::getModel)
        .addProperty("script", &ESM::LDoor::getScript)
        .addProperty("openSound", &ESM::LDoor::getOpenSound)
        .addProperty("closeSound", &ESM::LDoor::getCloseSound)
        .addFunction("load", &ESM::LDoor::load)
        .endClass()

        .beginClass<ESM::LBook>("Book")
        .addConstructor<void (*)()>()
        .addProperty("weight", &ESM::LBook::getWeight)
        .addProperty("value", &ESM::LBook::getValue)
        .addProperty("isScroll", &ESM::LBook::getIsScroll)
        .addProperty("skillId", &ESM::LBook::getSkillId)
        .addProperty("enchant", &ESM::LBook::getEnchant)
        .addProperty("name", &ESM::LBook::getName)
        .addProperty("model", &ESM::LBook::getModel)
        .addProperty("icon", &ESM::LBook::getIcon)
        .addProperty("script", &ESM::LBook::getScript)
        .addProperty("enchantd", &ESM::LBook::getEnchantId)
        .addProperty("text", &ESM::LBook::getText)
        .addProperty("id", &ESM::LBook::getId)
        .addFunction("load", &ESM::LBook::load)
        .endClass()

        .beginClass<ESM::LCellId>("CellId")
        .addConstructor<void (*)()>()
        .addProperty("x", &ESM::LCellId::getX)
        .addProperty("y", &ESM::LCellId::getY)
        .addProperty("paged", &ESM::LCellId::getPaged)
        .addProperty("defaultWorldspace", &ESM::LCellId::getDefaultWorldspace)
        .addFunction("load", &ESM::LCellId::load)
        .endClass()

        .beginClass<ESM::LVariant>("Variant")
        .addConstructor<void (*)()>()
        .addFunction("getType", &ESM::LVariant::getType)
        .addFunction("getString", &ESM::LVariant::getString)
        .addFunction("getInteger", &ESM::LVariant::getInteger)
        .addFunction("getFloat", &ESM::LVariant::getFloat)
        .endClass()

        .beginClass<ESM::LStatic>("Static")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LStatic::getRecordId)
        .addProperty("recordType", &ESM::LStatic::getRecordType)
        .addProperty("id", &ESM::LStatic::getId)
        .addProperty("model", &ESM::LStatic::getModel)
        .addFunction("load", &ESM::LStatic::load)
        .endClass()

        .beginClass<ESM::LSpell>("Spell")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LSpell::getRecordId)
        .addProperty("recordType", &ESM::LSpell::getRecordType)
        .addProperty("type", &ESM::LSpell::getType)
        .addProperty("cost", &ESM::LSpell::getCost)
        .addProperty("flags", &ESM::LSpell::getFlags)
        .addProperty("id", &ESM::LSpell::getId)
        .addProperty("name", &ESM::LSpell::getName)
        .addCFunction("effects", &ESM::LSpell::getEffects)
        .addFunction("load", &ESM::LSpell::load)
        .endClass()

        .beginClass<ESM::LSkill>("Skill")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LSkill::getRecordId)
        .addProperty("recordType", &ESM::LSkill::getRecordType)
        .addProperty("id", &ESM::LSkill::getId)
        .addProperty("attribute", &ESM::LSkill::getAttribute)
        .addProperty("specialization", &ESM::LSkill::getSpecialization)
        .addCFunction("useValue", &ESM::LSkill::getUseValue)
        .addProperty("index", &ESM::LSkill::getIndex)
        .addProperty("description", &ESM::LSkill::getDescription)
        .addFunction("indexToId", &ESM::LSkill::indexToId)
        .endClass()

        .beginClass<ESM::LMiscellaneous>("Miscellaneous")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LMiscellaneous::getRecordId)
        .addProperty("recordType", &ESM::LMiscellaneous::getRecordType)
        .addProperty("weight", &ESM::LMiscellaneous::getWeight)
        .addProperty("value", &ESM::LMiscellaneous::getValue)
        .addProperty("isKey", &ESM::LMiscellaneous::getIsKey)
        .addProperty("id", &ESM::LMiscellaneous::getId)
        .addProperty("name", &ESM::LMiscellaneous::getName)
        .addProperty("model", &ESM::LMiscellaneous::getModel)
        .addProperty("icon", &ESM::LMiscellaneous::getIcon)
        .addProperty("script", &ESM::LMiscellaneous::getScript)
        .addFunction("load", &ESM::LMiscellaneous::load)
        .endClass()

        .beginClass<ESM::LLandTexture>("LandTexture")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LLandTexture::getRecordId)
        .addProperty("recordType", &ESM::LLandTexture::getRecordType)
        .addProperty("id", &ESM::LLandTexture::getId)
        .addProperty("texture", &ESM::LLandTexture::getTexture)
        .addProperty("index", &ESM::LLandTexture::getIndex)
        .addFunction("load", &ESM::LLandTexture::load)
        .endClass()

        .beginClass<ESM::LIngredient>("Ingredient")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LIngredient::getRecordId)
        .addProperty("recordType", &ESM::LIngredient::getRecordType)
        .addProperty("weight", &ESM::LIngredient::getWeight)
        .addProperty("value", &ESM::LIngredient::getValue)
        .addCFunction("effectID", &ESM::LIngredient::getEffectID)
        .addCFunction("skills", &ESM::LIngredient::getSkills)
        .addCFunction("attributes", &ESM::LIngredient::getAttributes)
        .addProperty("id", &ESM::LIngredient::getId)
        .addProperty("name", &ESM::LIngredient::getName)
        .addProperty("model", &ESM::LIngredient::getModel)
        .addProperty("icon", &ESM::LIngredient::getIcon)
        .addProperty("script", &ESM::LIngredient::getScript)
        .addFunction("load", &ESM::LIngredient::load)
        .endClass()

        .beginClass<ESM::LGlobal>("Global")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LGlobal::getRecordId)
        .addProperty("recordType", &ESM::LGlobal::getRecordType)
        .addProperty("id", &ESM::LGlobal::getId)
        .addProperty("value", &ESM::LGlobal::getValue)
        .addFunction("load", &ESM::LGlobal::load)
        .endClass()

        .beginClass<ESM::LEnchantment>("Enchantment")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LEnchantment::getRecordId)
        .addProperty("recordType", &ESM::LEnchantment::getRecordType)
        .addProperty("type", &ESM::LEnchantment::getType)
        .addProperty("cost", &ESM::LEnchantment::getCost)
        .addProperty("charge", &ESM::LEnchantment::getCharge)
        .addProperty("autocalc", &ESM::LEnchantment::getAutocalc)
        .addProperty("id", &ESM::LEnchantment::getId)
        .addCFunction("effects", &ESM::LEnchantment::getEffects)
        .addFunction("load", &ESM::LEnchantment::load)
        .endClass()

        .beginClass<ESM::LCreature>("Creature")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LCreature::getRecordId)
        .addProperty("recordType", &ESM::LCreature::getRecordType)
        .addProperty("type", &ESM::LCreature::getType)
        .addProperty("level", &ESM::LCreature::getLevel)
        .addProperty("strength", &ESM::LCreature::getStrength)
        .addProperty("intelligence", &ESM::LCreature::getIntelligence)
        .addProperty("willpower", &ESM::LCreature::getWillpower)
        .addProperty("agility", &ESM::LCreature::getAgility)
        .addProperty("speed", &ESM::LCreature::getSpeed)
        .addProperty("endurance", &ESM::LCreature::getEndurance)
        .addProperty("personality", &ESM::LCreature::getPersonality)
        .addProperty("luck", &ESM::LCreature::getLuck)
        .addProperty("health", &ESM::LCreature::getHealth)
        .addProperty("mana", &ESM::LCreature::getMana)
        .addProperty("fatigue", &ESM::LCreature::getFatigue)
        .addProperty("soul", &ESM::LCreature::getSoul)
        .addProperty("combat", &ESM::LCreature::getCombat)
        .addProperty("magic", &ESM::LCreature::getMagic)
        .addProperty("stealth", &ESM::LCreature::getStealth)
        .addCFunction("attack", &ESM::LCreature::getAttack)
        .addProperty("gold", &ESM::LCreature::getGold)
        .addProperty("bloodType", &ESM::LCreature::getBloodType)
        .addProperty("flags", &ESM::LCreature::getFlags)
        .addProperty("persistent", &ESM::LCreature::getPersistent)
        .addProperty("scale", &ESM::LCreature::getScale)
        .addProperty("id", &ESM::LCreature::getId)
        .addProperty("model", &ESM::LCreature::getModel)
        .addProperty("name", &ESM::LCreature::getName)
        .addProperty("script", &ESM::LCreature::getScript)
        .addProperty("original", &ESM::LCreature::getOriginal)
        .addCFunction("inventory", &ESM::LCreature::getInventory)
        .addCFunction("spells", &ESM::LCreature::getSpells)
        .addCFunction("aiData", &ESM::LCreature::getAiData)
        .addCFunction("aiPackage", &ESM::LCreature::getAiPackage)
        .addCFunction("transport", &ESM::LCreature::getTransport)
        .addFunction("load", &ESM::LCreature::load)
        .endClass()

        .beginClass<ESM::LContItem>("ContItem")
        .addConstructor<void (*)()>()
        .addProperty("count", &ESM::LContItem::getCount)
        .addProperty("item", &ESM::LContItem::getItem)
        .endClass()

        .beginClass<ESM::LContainer>("Container")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LContainer::getRecordId)
        .addProperty("recordType", &ESM::LContainer::getRecordType)
        .addProperty("id", &ESM::LContainer::getId)
        .addProperty("name", &ESM::LContainer::getName)
        .addProperty("model", &ESM::LContainer::getModel)
        .addProperty("script", &ESM::LContainer::getScript)
        .addProperty("weight", &ESM::LContainer::getWeight)
        .addProperty("flags", &ESM::LContainer::getFlags)
        .addCFunction("inventory", &ESM::LContainer::getInventory)
        .addFunction("load", &ESM::LContainer::load)
        .endClass()

        .beginClass<ESM::LClothing>("Clothing")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LClothing::getRecordId)
        .addProperty("recordType", &ESM::LClothing::getRecordType)
        .addProperty("type", &ESM::LClothing::getType)
        .addProperty("weight", &ESM::LClothing::getWeight)
        .addProperty("value", &ESM::LClothing::getValue)
        .addProperty("enchant", &ESM::LClothing::getEnchant)
        .addCFunction("parts", &ESM::LClothing::getParts)
        .addProperty("id", &ESM::LClothing::getId)
        .addProperty("name", &ESM::LClothing::getName)
        .addProperty("model", &ESM::LClothing::getModel)
        .addProperty("icon", &ESM::LClothing::getIcon)
        .addProperty("enchantId", &ESM::LClothing::getEnchantId)
        .addProperty("script", &ESM::LClothing::getScript)
        .addFunction("load", &ESM::LClothing::load)
        .endClass()

        .beginClass<ESM::LClass>("Class")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LClass::getRecordId)
        .addProperty("recordType", &ESM::LClass::getRecordType)
        .addCFunction("specializationIds", &ESM::LClass::getSpecializationIds)
        .addCFunction("gmstSpecializationIds", &ESM::LClass::getGmstSpecializationIds)
        .addProperty("id", &ESM::LClass::getId)
        .addProperty("name", &ESM::LClass::getName)
        .addProperty("description", &ESM::LClass::getDescription)
        .addCFunction("attribute", &ESM::LClass::getAttribute)
        .addProperty("specialization", &ESM::LClass::getSpecialization)
        .addCFunction("skills", &ESM::LClass::getSkills)
        .addProperty("isPlayable", &ESM::LClass::getIsPlayable)
        .addProperty("calc", &ESM::LClass::getCalc)
        .addFunction("getSkill", &ESM::LClass::getSkill)
        .addFunction("load", &ESM::LClass::load)
        .endClass()

        .beginClass<ESM::LBirthSign>("BirthSign")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LBirthSign::getRecordId)
        .addProperty("recordType", &ESM::LBirthSign::getRecordType)
        .addProperty("id", &ESM::LBirthSign::getId)
        .addProperty("name", &ESM::LBirthSign::getName)
        .addProperty("description", &ESM::LBirthSign::getDescription)
        .addProperty("texture", &ESM::LBirthSign::getTexture)
        .addProperty("powers", &ESM::LBirthSign::getPowers)
        .addFunction("load", &ESM::LBirthSign::load)
        .endClass()

        .beginClass<ESM::LBodyPart>("BodyPart")
        .addConstructor<void (*)()>()
        .addProperty("recordId", &ESM::LBodyPart::getRecordId)
        .addProperty("recordType", &ESM::LBodyPart::getRecordType)
        .addProperty("id", &ESM::LBodyPart::getId)
        .addProperty("model", &ESM::LBodyPart::getModel)
        .addProperty("race", &ESM::LBodyPart::getRace)
        .addProperty("part", &ESM::LBodyPart::getPart)
        .addProperty("vampire", &ESM::LBodyPart::getVampire)
        .addProperty("flags", &ESM::LBodyPart::getFlags)
        .addProperty("type", &ESM::LBodyPart::getType)
        .addFunction("load", &ESM::LBodyPart::load)
        .endClass()

        .beginClass<ESM::LDest>("Dest")
        .addConstructor<void (*)()>()
        .addProperty("x", &ESM::LDest::getX)
        .addProperty("y", &ESM::LDest::getY)
        .addProperty("z", &ESM::LDest::getZ)
        .addProperty("rotX", &ESM::LDest::getRotX)
        .addProperty("rotY", &ESM::LDest::getRotY)
        .addProperty("rotZ", &ESM::LDest::getRotZ)
        .addProperty("cellName", &ESM::LDest::getCellName)
        .endClass()

        .endNamespace();
}
